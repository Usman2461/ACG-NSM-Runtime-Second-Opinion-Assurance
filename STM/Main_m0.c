/*************************************************************
    Main_m0.c
        Route level 0 procedure file
 *************************************************************/

#include "zipc_stub.h"
#include "Main_m0.h"
#include "ComSys_Paramram.h"
#include "action_decls.h"

static unsigned char ZMain_m0State[ZMain_M0STATEMAX];


void ZMain_m0StateView( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S0:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "1:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 0);
            break;
        case ZMain_M0S1:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "2:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 1);
            break;
        case ZMain_M0S2:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "3:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 2);
            break;
        case ZMain_M0S3:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "4:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 3);
            break;
        case ZMain_M0S4:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "5:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 4);
            break;
        case ZMain_M0S5:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "6:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 5);
            break;
        case ZMain_M0S6:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "7:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 6);
            break;
        case ZMain_M0S7:
            ZNOTIFY_STM_STATE_ENTRY(0, -1, "8:0");
            ZNOTIFY_STM_STATE_NO(0, -1, 7);
            break;
    }
}

void ZMain_m0IgnoreImpossibleVew( unsigned short evtNo )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S0:
            switch( evtNo )
            {
                case 0:
                    break;
                case 1:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:2");
                    break;
                case 2:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:3");
                    break;
                case 3:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:4");
                    break;
                case 4:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:5");
                    break;
                case 5:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:6");
                    break;
                case 6:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:7");
                    break;
                case 7:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:8");
                    break;
                case 8:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:9");
                    break;
                case 9:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:10");
                    break;
            }
            break;
        case ZMain_M0S1:
            switch( evtNo )
            {
                case 0:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:1");
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:4");
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:7");
                    break;
                case 7:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:8");
                    break;
                case 8:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:9");
                    break;
                case 9:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:10");
                    break;
            }
            break;
        case ZMain_M0S2:
            switch( evtNo )
            {
                case 0:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:1");
                    break;
                case 1:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:2");
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:5");
                    break;
                case 5:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:6");
                    break;
                case 6:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:7");
                    break;
                case 7:
                    break;
                case 8:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:9");
                    break;
                case 9:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:10");
                    break;
            }
            break;
        case ZMain_M0S3:
            switch( evtNo )
            {
                case 0:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:1");
                    break;
                case 1:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:2");
                    break;
                case 2:
                    break;
                case 3:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:4");
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:10");
                    break;
            }
            break;
        case ZMain_M0S4:
            switch( evtNo )
            {
                case 0:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:1");
                    break;
                case 1:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:2");
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:10");
                    break;
            }
            break;
        case ZMain_M0S5:
            switch( evtNo )
            {
                case 0:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:1");
                    break;
                case 1:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:2");
                    break;
                case 2:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:3");
                    break;
                case 3:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:4");
                    break;
                case 4:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:5");
                    break;
                case 5:
                    break;
                case 6:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:7");
                    break;
                case 7:
                    break;
                case 8:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:9");
                    break;
                case 9:
                    break;
            }
            break;
        case ZMain_M0S6:
            switch( evtNo )
            {
                case 0:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:1");
                    break;
                case 1:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:2");
                    break;
                case 2:
                    break;
                case 3:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:4");
                    break;
                case 4:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:5");
                    break;
                case 5:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:6");
                    break;
                case 6:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:7");
                    break;
                case 7:
                    break;
                case 8:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:9");
                    break;
                case 9:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:10");
                    break;
            }
            break;
        case ZMain_M0S7:
            switch( evtNo )
            {
                case 0:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:1");
                    break;
                case 1:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:2");
                    break;
                case 2:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:3");
                    break;
                case 3:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:4");
                    break;
                case 4:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:5");
                    break;
                case 5:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:6");
                    break;
                case 6:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:7");
                    break;
                case 7:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:8");
                    break;
                case 8:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:9");
                    break;
                case 9:
                    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "8:10");
                    break;
            }
            break;
    }
}

void ZMain_m0StateViewCansel( void )
{
    ZNOTIFY_STM_STATE_EXIT(0, -1, "1:0");
    ZNOTIFY_STM_STATE_EXIT(0, -1, "2:0");
    ZNOTIFY_STM_STATE_EXIT(0, -1, "3:0");
    ZNOTIFY_STM_STATE_EXIT(0, -1, "4:0");
    ZNOTIFY_STM_STATE_EXIT(0, -1, "5:0");
    ZNOTIFY_STM_STATE_EXIT(0, -1, "6:0");
    ZNOTIFY_STM_STATE_EXIT(0, -1, "7:0");
    ZNOTIFY_STM_STATE_EXIT(0, -1, "8:0");
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 0 Event : 0 Action function
 *****************************************/
static void ZMain_m0e0s0( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:1:0");
    {
        InitAll();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "1:1:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S1;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 1 Event : 1 Action function
 *****************************************/
static void ZMain_m0e1s1( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:2:0");
    {
        Brake();
        StartSigTmr();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:2:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S2;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 1 Event : 2 Action function
 *****************************************/
static void ZMain_m0e2s1( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:3");
    {
        SlowDown();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 2 Event : 2 Action function
 *****************************************/
static void ZMain_m0e2s2( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:3");
    {
        Hold();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 3 Event : 2 Action function
 *****************************************/
static void ZMain_m0e2s3( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:3:0");
    {
        Brake();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:3:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S2;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 4 Event : 2 Action function
 *****************************************/
static void ZMain_m0e2s4( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:3");
    {
        Hold();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 6 Event : 2 Action function
 *****************************************/
static void ZMain_m0e2s6( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:3");
    ZMain_m0StateViewCansel();
    ZMain_m0State[ZMain_M0] = ZMain_M0S2;
    ZMain_m0StateView();
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 2 Event : 3 Action function
 *****************************************/
static void ZMain_m0e3s2( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:4:0");
    {
        StartSafetyTmr();
        StartYldChk();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:4:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S3;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 4 Event : 3 Action function
 *****************************************/
static void ZMain_m0e3s4( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:4");
    {
        RecheckYld();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 1 Event : 4 Action function
 *****************************************/
static void ZMain_m0e4s1( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:5:0");
    {
        Brake();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:5:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S2;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 3 Event : 4 Action function
 *****************************************/
static void ZMain_m0e4s3( void )
{
    if( PassedLine )
    {
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:5:0");
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:5:2");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S5;
        ZMain_m0StateView();
    }
    else
    {
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:5:1");
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:5:3");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S2;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 4 Event : 4 Action function
 *****************************************/
static void ZMain_m0e4s4( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:5");
    ZMain_m0StateViewCansel();
    ZMain_m0State[ZMain_M0] = ZMain_M0S5;
    ZMain_m0StateView();
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 1 Event : 5 Action function
 *****************************************/
static void ZMain_m0e5s1( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "2:6");
    {
        SlowDown();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 3 Event : 5 Action function
 *****************************************/
static void ZMain_m0e5s3( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:6:0");
    {
        Brake();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:6:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S4;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 4 Event : 5 Action function
 *****************************************/
static void ZMain_m0e5s4( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:6");
    {
        Hold();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 5 Event : 5 Action function
 *****************************************/
static void ZMain_m0e5s5( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:6:0");
    {
        EmergBrake();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:6:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S4;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 3 Event : 6 Action function
 *****************************************/
static void ZMain_m0e6s3( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:7:0");
    {
        StartTurnTmr();
        SetPassedLine();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:7:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S5;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 4 Event : 6 Action function
 *****************************************/
static void ZMain_m0e6s4( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:7");
    ZMain_m0StateViewCansel();
    ZMain_m0State[ZMain_M0] = ZMain_M0S3;
    ZMain_m0StateView();
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 2 Event : 7 Action function
 *****************************************/
static void ZMain_m0e7s2( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "3:8");
    {
        RecheckSig();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 3 Event : 7 Action function
 *****************************************/
static void ZMain_m0e7s3( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:8");
    {
        RecheckAll();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 4 Event : 7 Action function
 *****************************************/
static void ZMain_m0e7s4( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:8");
    {
        RecheckAll();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 5 Event : 7 Action function
 *****************************************/
static void ZMain_m0e7s5( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:8:0");
    {
        WarnFault();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:8:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S7;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 6 Event : 7 Action function
 *****************************************/
static void ZMain_m0e7s6( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "7:8");
    ZMain_m0StateViewCansel();
    ZMain_m0State[ZMain_M0] = ZMain_M0S2;
    ZMain_m0StateView();
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 3 Event : 8 Action function
 *****************************************/
static void ZMain_m0e8s3( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:9:0");
    {
        Brake();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "4:9:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S6;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 4 Event : 8 Action function
 *****************************************/
static void ZMain_m0e8s4( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:9:0");
    {
        Brake();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "5:9:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S6;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 ) 
    State : 5 Event : 9 Action function
 *****************************************/
static void ZMain_m0e9s5( void )
{
    ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:10:0");
    {
        Resume();
        ZNOTIFY_STM_ACTION_ENTRY(0, -1, "6:10:1");
        ZMain_m0StateViewCansel();
        ZMain_m0State[ZMain_M0] = ZMain_M0S7;
        ZMain_m0StateView();
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 0 Event function
 *****************************************/
static void ZMain_m0e0( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S0:
            ZMain_m0e0s0();
            break;
        case ZMain_M0S1:
        case ZMain_M0S2:
        case ZMain_M0S3:
        case ZMain_M0S4:
        case ZMain_M0S5:
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 0 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 1 Event function
 *****************************************/
static void ZMain_m0e1( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S1:
            ZMain_m0e1s1();
            break;
        case ZMain_M0S2:
        case ZMain_M0S3:
        case ZMain_M0S4:
            ZMain_m0IgnoreImpossibleVew( 1 );
            break;
        case ZMain_M0S0:
        case ZMain_M0S5:
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 1 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 2 Event function
 *****************************************/
static void ZMain_m0e2( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S1:
            ZMain_m0e2s1();
            break;
        case ZMain_M0S2:
            ZMain_m0e2s2();
            break;
        case ZMain_M0S3:
            ZMain_m0e2s3();
            break;
        case ZMain_M0S4:
            ZMain_m0e2s4();
            break;
        case ZMain_M0S6:
            ZMain_m0e2s6();
            break;
        case ZMain_M0S0:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 2 );
            break;
        case ZMain_M0S5:
            ZMain_m0IgnoreImpossibleVew( 2 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 3 Event function
 *****************************************/
static void ZMain_m0e3( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S2:
            ZMain_m0e3s2();
            break;
        case ZMain_M0S4:
            ZMain_m0e3s4();
            break;
        case ZMain_M0S0:
        case ZMain_M0S1:
        case ZMain_M0S3:
        case ZMain_M0S5:
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 3 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 4 Event function
 *****************************************/
static void ZMain_m0e4( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S1:
            ZMain_m0e4s1();
            break;
        case ZMain_M0S3:
            ZMain_m0e4s3();
            break;
        case ZMain_M0S4:
            ZMain_m0e4s4();
            break;
        case ZMain_M0S0:
        case ZMain_M0S5:
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 4 );
            break;
        case ZMain_M0S2:
            ZMain_m0IgnoreImpossibleVew( 4 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 5 Event function
 *****************************************/
static void ZMain_m0e5( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S1:
            ZMain_m0e5s1();
            break;
        case ZMain_M0S3:
            ZMain_m0e5s3();
            break;
        case ZMain_M0S4:
            ZMain_m0e5s4();
            break;
        case ZMain_M0S5:
            ZMain_m0e5s5();
            break;
        case ZMain_M0S0:
        case ZMain_M0S2:
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 5 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 6 Event function
 *****************************************/
static void ZMain_m0e6( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S3:
            ZMain_m0e6s3();
            break;
        case ZMain_M0S4:
            ZMain_m0e6s4();
            break;
        case ZMain_M0S0:
        case ZMain_M0S1:
        case ZMain_M0S2:
        case ZMain_M0S5:
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 6 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 7 Event function
 *****************************************/
static void ZMain_m0e7( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S2:
            ZMain_m0e7s2();
            break;
        case ZMain_M0S3:
            ZMain_m0e7s3();
            break;
        case ZMain_M0S4:
            ZMain_m0e7s4();
            break;
        case ZMain_M0S5:
            ZMain_m0e7s5();
            break;
        case ZMain_M0S6:
            ZMain_m0e7s6();
            break;
        case ZMain_M0S0:
        case ZMain_M0S1:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 7 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 8 Event function
 *****************************************/
static void ZMain_m0e8( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S3:
            ZMain_m0e8s3();
            break;
        case ZMain_M0S4:
            ZMain_m0e8s4();
            break;
        case ZMain_M0S0:
        case ZMain_M0S1:
        case ZMain_M0S2:
        case ZMain_M0S5:
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 8 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event : 9 Event function
 *****************************************/
static void ZMain_m0e9( void )
{
    switch( ZMain_m0State[ZMain_M0] )
    {
        case ZMain_M0S5:
            ZMain_m0e9s5();
            break;
        case ZMain_M0S6:
        case ZMain_M0S7:
            ZMain_m0IgnoreImpossibleVew( 9 );
            break;
        case ZMain_M0S0:
        case ZMain_M0S1:
        case ZMain_M0S2:
        case ZMain_M0S3:
        case ZMain_M0S4:
            ZMain_m0IgnoreImpossibleVew( 9 );
            break;
        default:
            break;
    }
}

/*****************************************
    Main TL_Main( level : 0 )
    Event analysis function
 *****************************************/
void ZMain_m0Call( void )
{
    ZNOTIFY_STM_EVENT_INIT(0, -1);
    if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_START") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:1");
        ZNOTIFY_STM_EVENT_NO(0, -1, 0);
        ZMain_m0e0();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_STOPLINE_REACH") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:2");
        ZNOTIFY_STM_EVENT_NO(0, -1, 1);
        ZMain_m0e1();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_SIG_RED") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:3");
        ZNOTIFY_STM_EVENT_NO(0, -1, 2);
        ZMain_m0e2();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_SIG_GREEN_LT") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:4");
        ZNOTIFY_STM_EVENT_NO(0, -1, 3);
        ZMain_m0e3();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_SIG_YELLOW") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:5");
        ZNOTIFY_STM_EVENT_NO(0, -1, 4);
        ZMain_m0e4();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_YIELD_BLOCK") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:6");
        ZNOTIFY_STM_EVENT_NO(0, -1, 5);
        ZMain_m0e5();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_YIELD_CLEAR") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:7");
        ZNOTIFY_STM_EVENT_NO(0, -1, 6);
        ZMain_m0e6();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_TMR_EXPIRED") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:8");
        ZNOTIFY_STM_EVENT_NO(0, -1, 7);
        ZMain_m0e7();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_TMR_LOW") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:9");
        ZNOTIFY_STM_EVENT_NO(0, -1, 8);
        ZMain_m0e8();
    }
    else if( ZNOTIFY_CHECK_EVENT(&ZMainEvent[0], "EV_INTSEC_EXIT") )
    {
        ZNOTIFY_STM_EVENT_ENTRY(0, -1, "0:10");
        ZNOTIFY_STM_EVENT_NO(0, -1, 9);
        ZMain_m0e9();
    }
}

/*****************************************
    Main Route 0
    Initial function
 *****************************************/
void ZMain_m0Init( void )
{
    ZMain_m0State[ZMain_M0] = ZMain_M0S0;
    ZMain_m0StateView();
}

/* --- added accessor for integration (state array is static) --- */
int zipc_get_state_internal( void )
{
    return (int)ZMain_m0State[ZMain_M0];
}
