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
