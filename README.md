# ACG-NSM

## Runtime Second-Opinion Assurance for Safe, Law-Compliant, and Traceable End-to-End Autonomous Driving

**ACG-NSM** (Adaptive Confidence-Gated Neural–State Machine) is a runtime-assurance framework for end-to-end autonomous driving.

The framework is designed as an **independent second opinion** around a high-performance learned driving policy such as **TransFuser++**. The nominal end-to-end policy remains responsible for normal driving, while ACG-NSM independently evaluates whether the proposed command is physically safe, legally admissible, and supported by sufficiently trustworthy perception.

The runtime decision is intentionally simple:

> **Accept the nominal command unchanged, or suppress unsafe longitudinal authority.**

ACG-NSM does **not** replace the learned planner with a second learned controller.

---

## Overview

At every control tick, the system executes two parallel paths:

```text
                    Shared sensor observations
                             |
               +-------------+-------------+
               |                           |
               v                           v
        TransFuser++                    ACG-NSM
       nominal policy              assurance channel
               |                           |
               |                 Seven-class YOLO26
               |                           |
               |                 Confidence calibration
               |                           |
               |                Bayesian confidence of
               |                      absence
               |                           |
               |                  Physical-risk assessor
               |                           |
               |                  Traffic-law assessor
               |                           |
               |                  Risk-Legality-
               |                 Confidence bridge
               |                           |
               |                  Compiled formal STM
               |                           |
               +-------------+-------------+
                             |
                      Runtime arbiter
                             |
                  ACCEPT or SUPPRESS
                             |
                     Executed command
                             |
                      Causal witness
```

The nominal and assurance channels share sensor observations but do not share learned internal representations or detections.

---

## Main Contributions

ACG-NSM provides:

* **Independent runtime assurance** around a frozen end-to-end driving policy.
* **Binary accept–suppress arbitration** without introducing a replacement planner.
* **Seven-class YOLO26 assurance perception** for:

  * pedestrian
  * vehicle
  * cyclist
  * traffic sign
  * red traffic light
  * yellow traffic light
  * green traffic light
* **Temperature-scaled detection confidence**.
* **Evidence-aware Bayesian confidence of absence** for complete missed detections.
* **Physical-risk assessment** using stopping distance, TTC, proximity, and ego speed.
* **Article-level traffic-law reasoning** with most-restrictive rule aggregation.
* **Risk–Legality–Confidence (RLC) event injection** into a formal state machine.
* **Compiled C formal execution**.
* **Bounded online adaptation** inside statically declared safety intervals.
* **Per-tick causal audit witnesses** from sensor evidence to executed control.
* **Exhaustive verification** of the finite permission model.

---

## Runtime Assurance Logic

Let the nominal TransFuser++ command be \(u_N\), and let ACG-NSM determine whether the corresponding nominal maneuver is admissible.

The executed command is:

```text
u_exec = u_N                         if admissible
u_exec = S(u_N, scene)               otherwise
```

where `S(.)` suppresses unsafe longitudinal authority.

The assurance branch acts only as an **admissibility reference**. It does not synthesize or substitute an independent learned driving maneuver.

---

## Confidence-Gated Perception

### Positive detections

Positive YOLO26 detections are calibrated using temperature scaling.

Reproducibility values:

| Quantity                                    |  Value |
| ------------------------------------------- | -----: |
| Temperature \(T\)                           |    2.3 |
| Calibration detections                      | 22,890 |
| ECE before calibration                      |  0.179 |
| ECE after calibration                       |  0.033 |
| Empirical calibration residual \(\epsilon\) |  0.033 |

### Confidence of absence

A missing detection is not interpreted as certain absence.

For a relevant class \(c\),

```text
P(H_c | not D_c, q)
```

is estimated from:

* measured class recall,
* prior class presence probability,
* observation quality,
* the probability of non-detection.

The confidence assigned to an absence claim is

```text
c_abs = 1 - P(H_c | not D_c, q)
```

Poor visibility, truncation, distance, or degraded frame quality reduces the confidence of absence.

---

## Rig-Matched Assurance Dataset

The assurance detector is trained using a CARLA corpus captured using the same camera geometry used at runtime.

| Property                   |      Value |
| -------------------------- | ---------: |
| Total frames               |     15,000 |
| Training frames            |     13,120 |
| Validation frames          |      1,880 |
| Training temporal blocks   |        219 |
| Validation temporal blocks |         31 |
| Total labeled instances    |    186,382 |
| Average labels/frame       |       12.4 |
| Camera resolution          | 1024 × 256 |
| Camera field of view       |       110° |

### Dataset composition

| Class          |       Train | Validation |       Total |
| -------------- | ----------: | ---------: | ----------: |
| Pedestrian     |      11,423 |      1,635 |      13,058 |
| Vehicle        |      60,010 |      7,483 |      67,493 |
| Light (red)    |      26,853 |      3,986 |      30,839 |
| Light (yellow) |       3,116 |        500 |       3,616 |
| Light (green)  |       7,918 |      1,072 |       8,990 |
| Cyclist        |      10,769 |      1,272 |      12,041 |
| Traffic sign   |      44,747 |      5,598 |      50,345 |
| **Total**      | **164,836** | **21,546** | **186,382** |

The detector achieves an **instance-weighted recall of 91.2%** on the held-out 1,880-frame validation split.

---

## Physical-Risk Model

The physical-risk assessor combines:

* braking-distance risk,
* time-to-collision,
* proximity,
* ego-speed amplification.

The braking-distance criterion is based on:

```text
d_brake(v) = v * t_react + v^2 / (2 * mu * g)
```

The deployed parameters are:

| Parameter                      | Value |
| ------------------------------ | ----: |
| Reaction-time allowance        | 0.3 s |
| Tyre-road friction coefficient |   0.7 |
| Braking-risk weight            |  0.45 |
| TTC-risk weight                |  0.30 |
| Proximity-risk weight          |  0.25 |

Risk is quantized into:

```text
LOW
MED
HIGH
CRITICAL
```

with asymmetric hysteresis to avoid unsafe transient downgrades.

---

## Traffic-Law Assurance

The legality assessor evaluates candidate maneuvers against an article-structured rule base.

Representative rule families include:

* traffic-signal compliance,
* pedestrian yielding,
* oncoming-traffic right of way,
* following distance,
* speed limits,
* lane-marking restrictions.

When several rules apply simultaneously, the final decision uses the **most restrictive applicable verdict**.

The governing traffic-law article identifier is propagated into the runtime witness.

---

## RLC Bridge

The Risk–Legality–Confidence bridge transforms uncertainty-bearing continuous perception into the finite event alphabet required by the formal state machine.

For each field:

```text
if confidence >= threshold:
    use observation
else:
    substitute conservative fail-safe assumption
```

Examples:

```text
Untrusted pedestrian   -> assume pedestrian present
Untrusted signal       -> assume restrictive compatible phase
Untrusted oncoming     -> assume oncoming traffic present
Untrusted risk         -> freeze last trusted risk tier
Persistent distrust    -> sensor-fault hold
```

Uncertainty may therefore **remove permission but cannot create new permission**.

---

## Deployed Parameters

| Parameter                        | Value / hard interval |
| -------------------------------- | --------------------- |
| LOW/MED boundary                 | 0.30 [0.25, 0.40]     |
| MED/HIGH boundary                | 0.70 [0.60, 0.75]     |
| CRITICAL boundary                | **0.90 immutable**    |
| Risk hysteresis                  | 0.05 / 5 ticks        |
| Obstacle confidence gate         | 0.85 [0.80, 0.95]     |
| Pedestrian confidence gate       | 0.88 [0.83, 0.95]     |
| Signal confidence gate           | 0.92 [0.88, 0.97]     |
| Oncoming confidence gate         | 0.88 [0.83, 0.95]     |
| Persistent distrust threshold    | 10 ticks              |
| Adaptation dead band             | 0.10–0.30             |
| Samples before adaptation update | 10                    |
| Calibration residual             | 0.033                 |

At the 20 Hz control rate, 10 distrust ticks correspond to **0.5 s**.

---

## Bounded Adaptation

The adaptation module reduces unnecessary interventions while remaining inside a statically verified safety envelope.

The controller observes false alarms and true alarms and estimates:

```text
nu_hat = FA / (FA + TA)
```

Adaptation then follows:

```text
if nu_hat > 0.30:
    move in nuisance-reducing direction

elif nu_hat < 0.10:
    move in caution-restoring direction

else:
    retain current parameters
```

Every update is projected back into its declared hard interval.

The critical risk boundary

```text
r_crit = 0.90
```

is immutable.

### Adaptation result

| Configuration          | False-alarm rate | Missed-hazard rate |
| ---------------------- | ---------------: | -----------------: |
| Static / no adaptation |            67.2% |               0.0% |
| Adaptive ACG-NSM       |             5.5% |               0.0% |
| Relative reduction     |        **91.8%** |                  — |

Evaluation: **20 trials × 500 ticks**.

---

## Formal Verification

The finite permission model is exhaustively checked.

| Verification item                     |    Result |
| ------------------------------------- | --------: |
| Scene-domain size                     |       256 |
| Comparable hazard-ordered scene pairs |     7,034 |
| Antitonicity violations               |     **0** |
| Formal states                         |         8 |
| Formal events                         |        10 |
| Transitions                           |        27 |
| Reachability diameter                 |         5 |
| Model-code correspondence             | **25/25** |

For every comparable pair

```text
s <= s'
```

the verification checks:

```text
Pi(s') subseteq Pi(s)
```

meaning that increasing hazard cannot expand the permission set.

---

## Decision Correctness Under Perception Degradation

The controlled decision-correctness experiment evaluates **4,000 decisions at each degradation level**.

The ungated nominal interpretation becomes increasingly unsafe as perception degrades, while the confidence-gated ACG-NSM interpretation reaches:

```text
0.00% residual unsafe decisions
```

from degradation **0.4 onward**.

---

## Runtime Second-Opinion Suppression

A separate controlled arbitration study evaluates TransFuser++ nominal decisions against the ACG-NSM admissibility channel.

| Degradation | Nominal unsafe | Interception recall | Residual unsafe |
| ----------: | -------------: | ------------------: | --------------: |
|         0.0 |          0.35% |              21.43% |          0.275% |
|         0.2 |          2.00% |              96.25% |          0.075% |
|         0.4 |          3.63% |          **99.31%** |          0.025% |
|         0.6 |          4.73% |         **100.00%** |          0.000% |
|         0.8 |          6.05% |         **100.00%** |          0.000% |
|         1.0 |          8.10% |         **100.00%** |          0.000% |

Interception recall reaches approximately **99% at degradation 0.4** and **100% from degradation 0.6 onward**.

---

## Complete-Miss Handling

Under the measured **8.8% detector miss rate**, evidence-aware absence changes the complete-miss unsafe-decision rate from:

```text
Naive absence           1.38%
Evidence-aware absence  0.00%
```

while maintaining a comparable conservative-decision rate.

---

## Component Ablation

| Configuration | Red light | High-speed obstacle | Low-confidence pedestrian | Oncoming turn | Clear drive FP |
| ------------- | --------: | ------------------: | ------------------------: | ------------: | -------------: |
| Full ACG-NSM  |        0% |                  0% |                        0% |            0% |             0% |
| No gate       |        0% |                  0% |                      100% |            0% |             0% |
| No adaptation |        0% |                  0% |                        0% |            0% |             0% |
| Risk only     |      100% |                  0% |                      100% |          100% |             0% |
| Legality only |        0% |                100% |                        0% |            0% |             0% |

Each cell contains **50 repetitions**.

The experiment isolates the complementary roles of:

* confidence gating,
* physical-risk assessment,
* traffic-law reasoning.

---

## Localization

LiDAR odometry provides the localization quantities used by the assurance channel.

| Scenario             | ATE RMSE (m) |    RPE (m) |
| -------------------- | -----------: | ---------: |
| Signalized left turn |        0.897 |     0.0187 |
| Highway cut-in       |        0.670 |     0.0164 |
| Pedestrian crossing  |        0.297 |     0.0096 |
| Adverse weather      |        0.256 |     0.0085 |
| **Aggregate**        |    **0.530** | **0.0133** |

---

## Runtime Cost

| Stage                      |            Runtime |
| -------------------------- | -----------------: |
| YOLO26 assurance inference |       1.60 ms mean |
| RLC bridge + compiled STM  |       0.24 ms mean |
| Complete assurance path    |   **1.84 ms mean** |
| Isolated arbitration       |           0.018 ms |
| Formal bridge + STM        |     0.34 ms at P95 |
| Formal bridge + STM        | 1.25 ms worst case |

---

## Causal Audit Witness

Every valid runtime decision can emit a structured causal witness containing:

* simulator tick and sensor/frame identity,
* ego state,
* assurance detector outputs,
* calibrated positive confidence,
* Bayesian absence confidence,
* field-specific gate results,
* fail-safe substitutions,
* physical-risk score and tier,
* stopping-distance/TTC evidence,
* legal-action mask,
* governing traffic-law article,
* RLC events,
* persistent-distrust state,
* formal state transition,
* nominal target speed and control,
* binary accept–suppress result,
* executed target speed and control,
* disagreement magnitude,
* runtime timing information.

This allows a decision to be replayed backward from the executed command to the evidence and rule that caused it.

---

## Repository Structure

A typical repository layout is:

```text
ACG-NSM/
|
+-- src/
|   +-- 51_suppression_arbiter.py
|   +-- 52_acgnsm_channel.py
|   +-- 53_guided_agent.py
|   +-- 80_record_video.py
|   +-- ...
|
+-- stm/
|   +-- generated C state-machine source
|   +-- compiled runtime library
|
+-- runs/
|   +-- detector weights
|   +-- calibration artifacts
|
+-- results/
|   +-- confidence_calibration.json
|   +-- reliability_diagram.png
|   +-- slam_metrics.json
|   +-- slam_result.png
|   +-- ablation_results.json
|   +-- adaptation_benefit.json
|   +-- second_opinion_suppression.json
|   +-- ...
|
+-- supplementary/
|   +-- ACG_NSM_Supplementary_Material.pdf
|
+-- README.md
```

---

## Reproduction Workflow

### 1. Prepare CARLA

Experiments use:

```text
CARLA 0.9.15
```

with the CARLA Garage / Leaderboard-compatible TransFuser++ evaluation pipeline.

### 2. Prepare the assurance dataset

Capture the runtime-matched camera stream:

```text
Resolution: 1024 x 256
FOV:        110 degrees
```

Preserve temporal blocks when constructing the train/validation split.

### 3. Train the seven-class YOLO26 detector

Train using the seven assurance classes and the rig-matched CARLA dataset.

### 4. Calibrate detector confidence

Fit a scalar temperature on the held-out validation detections.

Target reproduction values:

```text
T              = 2.3
ECE before     = 0.179
ECE after      = 0.033
```

### 5. Estimate confidence of absence

Measure held-out class recall and combine it with observation quality and prior presence probability.

### 6. Verify the formal permission model

Enumerate the finite scene space and verify antitonicity:

```text
Scenes             = 256
Comparable pairs   = 7,034
Violations         = 0
```

### 7. Build the compiled STM runtime

Generate the state-machine implementation as C and compile it into the runtime library used by the assurance channel.

### 8. Run ACG-NSM with TransFuser++

Use the guided agent with the nominal TransFuser++ checkpoint held fixed.

The runtime sequence is:

```text
nominal policy
    ->
independent assurance perception
    ->
confidence / absence calibration
    ->
risk + legality
    ->
RLC gate
    ->
compiled formal state machine
    ->
accept / suppress
    ->
executed command
    ->
audit witness
```

### 9. Recompute evaluation metrics

Use the machine-readable result artifacts to reproduce:

* calibration error,
* detector performance,
* localization accuracy,
* decision correctness,
* interception recall,
* residual unsafe rate,
* component ablation,
* bounded-adaptation benefit,
* formal verification,
* runtime latency.

---

## Supplementary Material

Detailed reproducibility values, algorithms, parameter tables, formal-verification results, metric definitions, and machine-readable artifact mappings are provided in:

```text
ACG_NSM_Supplementary_Material.pdf
```

---

## Paper

**ACG-NSM: Runtime Second-Opinion Assurance for Safe, Law-Compliant, and Traceable End-to-End Autonomous Driving**

Muhammad Usman Arshad, Zhou Kuanjiu, and Yicong Li
School of Software Technology
Dalian University of Technology
Dalian, China

---

## Citation

If this work is useful in your research, please cite the paper:

```bibtex
@article{arshad2026acgnsm,
  title   = {ACG-NSM: Runtime Second-Opinion Assurance for Safe,
             Law-Compliant, and Traceable End-to-End Autonomous Driving},
  author  = {Arshad, Muhammad Usman and Zhou, Kuanjiu and Li, Yicong},
  journal = {IEEE Transactions on Vehicular Technology},
  year    = {2026}
}
```

---

## Core Design Principle

> Preserve the learned driver's command when it is admissible; use an independently checkable, confidence-aware formal second opinion to suppress longitudinal authority when the command conflicts with physical safety, traffic-law constraints, or trustworthy evidence.
