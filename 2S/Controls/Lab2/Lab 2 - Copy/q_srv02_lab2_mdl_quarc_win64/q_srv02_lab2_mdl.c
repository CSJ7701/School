/*
 * q_srv02_lab2_mdl.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_srv02_lab2_mdl".
 *
 * Model version              : 5.4
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Tue Feb 27 15:16:16 2024
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "q_srv02_lab2_mdl.h"
#include "q_srv02_lab2_mdl_private.h"
#include "q_srv02_lab2_mdl_dt.h"

/* Block signals (default storage) */
B_q_srv02_lab2_mdl_T q_srv02_lab2_mdl_B;

/* Continuous states */
X_q_srv02_lab2_mdl_T q_srv02_lab2_mdl_X;

/* Block states (default storage) */
DW_q_srv02_lab2_mdl_T q_srv02_lab2_mdl_DW;

/* Real-time model */
static RT_MODEL_q_srv02_lab2_mdl_T q_srv02_lab2_mdl_M_;
RT_MODEL_q_srv02_lab2_mdl_T *const q_srv02_lab2_mdl_M = &q_srv02_lab2_mdl_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  q_srv02_lab2_mdl_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void q_srv02_lab2_mdl_output(void)
{
  real_T temp;
  real_T u0;
  real_T u2;
  if (rtmIsMajorTimeStep(q_srv02_lab2_mdl_M)) {
    /* set solver stop time */
    if (!(q_srv02_lab2_mdl_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&q_srv02_lab2_mdl_M->solverInfo,
                            ((q_srv02_lab2_mdl_M->Timing.clockTickH0 + 1) *
        q_srv02_lab2_mdl_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&q_srv02_lab2_mdl_M->solverInfo,
                            ((q_srv02_lab2_mdl_M->Timing.clockTick0 + 1) *
        q_srv02_lab2_mdl_M->Timing.stepSize0 +
        q_srv02_lab2_mdl_M->Timing.clockTickH0 *
        q_srv02_lab2_mdl_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(q_srv02_lab2_mdl_M)) {
    q_srv02_lab2_mdl_M->Timing.t[0] = rtsiGetT(&q_srv02_lab2_mdl_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(q_srv02_lab2_mdl_M)) {
    /* S-Function (hil_read_analog_timebase_block): '<S7>/HIL Read Analog Timebase' */

    /* S-Function Block: q_srv02_lab2_mdl/SRV02-ET Speed/SRV02-ET/HIL Read Analog Timebase (hil_read_analog_timebase_block) */
    {
      t_error result;
      result = hil_task_read_analog
        (q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Task, 1,
         &q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      }

      q_srv02_lab2_mdl_B.HILReadAnalogTimebase_o1 =
        q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Buffer[0];
      q_srv02_lab2_mdl_B.HILReadAnalogTimebase_o2 =
        q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Buffer[1];
    }

    /* S-Function (hil_read_encoder_block): '<S7>/HIL Read Encoder' */

    /* S-Function Block: q_srv02_lab2_mdl/SRV02-ET Speed/SRV02-ET/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(q_srv02_lab2_mdl_DW.HILInitialize_Card,
        &q_srv02_lab2_mdl_P.HILReadEncoder_channels, 1,
        &q_srv02_lab2_mdl_DW.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      } else {
        q_srv02_lab2_mdl_B.HILReadEncoder =
          q_srv02_lab2_mdl_DW.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<S7>/Encoder Calibration  (rad//count)' */
    q_srv02_lab2_mdl_B.EncoderCalibrationradcount = q_srv02_lab2_mdl_P.K_ENC *
      q_srv02_lab2_mdl_B.HILReadEncoder;

    /* MultiPortSwitch: '<S7>/Position Source Switch' incorporates:
     *  Constant: '<S5>/Pos Src'
     */
    if ((int32_T)q_srv02_lab2_mdl_P.PosSrc_Value == 1) {
      /* Gain: '<S7>/Potentiometer Calibration  (rad//V)' */
      q_srv02_lab2_mdl_B.PotentiometerCalibrationradV = q_srv02_lab2_mdl_P.K_POT
        * q_srv02_lab2_mdl_B.HILReadAnalogTimebase_o1;

      /* MultiPortSwitch: '<S7>/Position Source Switch' */
      q_srv02_lab2_mdl_B.PositionSourceSwitch =
        q_srv02_lab2_mdl_B.PotentiometerCalibrationradV;
    } else {
      /* MultiPortSwitch: '<S7>/Position Source Switch' */
      q_srv02_lab2_mdl_B.PositionSourceSwitch =
        q_srv02_lab2_mdl_B.EncoderCalibrationradcount;
    }

    /* End of MultiPortSwitch: '<S7>/Position Source Switch' */

    /* Gain: '<S7>/Tachometer Calibration  (rad//s//V)' */
    q_srv02_lab2_mdl_B.TachometerCalibrationradsV = q_srv02_lab2_mdl_P.K_TACH *
      q_srv02_lab2_mdl_B.HILReadAnalogTimebase_o2;
  }

  /* TransferFcn: '<S7>/Encoder High-Pass Filter' */
  q_srv02_lab2_mdl_B.EncoderHighPassFilter = 0.0;
  q_srv02_lab2_mdl_B.EncoderHighPassFilter +=
    q_srv02_lab2_mdl_P.EncoderHighPassFilter_C[0] *
    q_srv02_lab2_mdl_X.EncoderHighPassFilter_CSTATE[0];
  q_srv02_lab2_mdl_B.EncoderHighPassFilter +=
    q_srv02_lab2_mdl_P.EncoderHighPassFilter_C[1] *
    q_srv02_lab2_mdl_X.EncoderHighPassFilter_CSTATE[1];

  /* MultiPortSwitch: '<S7>/Velocity Source Switch' incorporates:
   *  Constant: '<Root>/Spd Src'
   */
  if ((int32_T)q_srv02_lab2_mdl_P.SpdSrc_Value == 1) {
    /* MultiPortSwitch: '<S7>/Velocity Source Switch' */
    q_srv02_lab2_mdl_B.VelocitySourceSwitch =
      q_srv02_lab2_mdl_B.TachometerCalibrationradsV;
  } else {
    /* MultiPortSwitch: '<S7>/Velocity Source Switch' */
    q_srv02_lab2_mdl_B.VelocitySourceSwitch =
      q_srv02_lab2_mdl_B.EncoderHighPassFilter;
  }

  /* End of MultiPortSwitch: '<S7>/Velocity Source Switch' */

  /* SignalGenerator: '<Root>/Signal Generator' */
  temp = q_srv02_lab2_mdl_P.SignalGenerator_Frequency *
    q_srv02_lab2_mdl_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    /* SignalGenerator: '<Root>/Signal Generator' */
    q_srv02_lab2_mdl_B.SignalGenerator =
      q_srv02_lab2_mdl_P.SignalGenerator_Amplitude;
  } else {
    /* SignalGenerator: '<Root>/Signal Generator' */
    q_srv02_lab2_mdl_B.SignalGenerator =
      -q_srv02_lab2_mdl_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Gain: '<S1>/Slider Gain' */
  q_srv02_lab2_mdl_B.SliderGain = q_srv02_lab2_mdl_P.AmplitudeV_gain *
    q_srv02_lab2_mdl_B.SignalGenerator;
  if (rtmIsMajorTimeStep(q_srv02_lab2_mdl_M)) {
    /* Gain: '<S2>/Slider Gain' incorporates:
     *  Constant: '<Root>/Constant'
     */
    q_srv02_lab2_mdl_B.SliderGain_h = q_srv02_lab2_mdl_P.OffsetV_gain *
      q_srv02_lab2_mdl_P.Constant_Value;
  }

  /* Sum: '<Root>/Vi' */
  q_srv02_lab2_mdl_B.Vi = q_srv02_lab2_mdl_B.SliderGain +
    q_srv02_lab2_mdl_B.SliderGain_h;

  /* Gain: '<S8>/Direction Convention: (Right-Hand) system' */
  q_srv02_lab2_mdl_B.DirectionConventionRightHandsys =
    q_srv02_lab2_mdl_P.DirectionConventionRightHandsys * q_srv02_lab2_mdl_B.Vi;

  /* Saturate: '<S8>/Amplifier  Saturation (V)' */
  temp = -q_srv02_lab2_mdl_P.VMAX_AMP;
  u0 = q_srv02_lab2_mdl_B.DirectionConventionRightHandsys;
  u2 = q_srv02_lab2_mdl_P.VMAX_AMP;
  if (u0 > u2) {
    /* Saturate: '<S8>/Amplifier  Saturation (V)' */
    q_srv02_lab2_mdl_B.AmplifierSaturationV = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S8>/Amplifier  Saturation (V)' */
    q_srv02_lab2_mdl_B.AmplifierSaturationV = temp;
  } else {
    /* Saturate: '<S8>/Amplifier  Saturation (V)' */
    q_srv02_lab2_mdl_B.AmplifierSaturationV = u0;
  }

  /* End of Saturate: '<S8>/Amplifier  Saturation (V)' */

  /* Gain: '<S8>/Inverse Amplifier  Gain (V//V)' */
  temp = 1.0 / q_srv02_lab2_mdl_P.K_AMP;

  /* Gain: '<S8>/Inverse Amplifier  Gain (V//V)' */
  q_srv02_lab2_mdl_B.InverseAmplifierGainVV = temp *
    q_srv02_lab2_mdl_B.AmplifierSaturationV;

  /* Saturate: '<S8>/DACB Saturation (V)' */
  temp = -q_srv02_lab2_mdl_P.VMAX_DAC;
  u0 = q_srv02_lab2_mdl_B.InverseAmplifierGainVV;
  u2 = q_srv02_lab2_mdl_P.VMAX_DAC;
  if (u0 > u2) {
    /* Saturate: '<S8>/DACB Saturation (V)' */
    q_srv02_lab2_mdl_B.DACBSaturationV = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S8>/DACB Saturation (V)' */
    q_srv02_lab2_mdl_B.DACBSaturationV = temp;
  } else {
    /* Saturate: '<S8>/DACB Saturation (V)' */
    q_srv02_lab2_mdl_B.DACBSaturationV = u0;
  }

  /* End of Saturate: '<S8>/DACB Saturation (V)' */
  if (rtmIsMajorTimeStep(q_srv02_lab2_mdl_M)) {
    /* S-Function (hil_write_analog_block): '<S7>/HIL Write Analog' */

    /* S-Function Block: q_srv02_lab2_mdl/SRV02-ET Speed/SRV02-ET/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(q_srv02_lab2_mdl_DW.HILInitialize_Card,
        &q_srv02_lab2_mdl_P.HILWriteAnalog_channels, 1,
        &q_srv02_lab2_mdl_B.DACBSaturationV);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<S8>/Amplifier  Gain (V//V)' */
  temp = -q_srv02_lab2_mdl_P.K_AMP;

  /* Gain: '<S8>/Amplifier  Gain (V//V)' */
  q_srv02_lab2_mdl_B.AmplifierGainVV = temp * q_srv02_lab2_mdl_B.DACBSaturationV;
  if (rtmIsMajorTimeStep(q_srv02_lab2_mdl_M)) {
    /* S-Function (hil_write_digital_block): '<S7>/HIL Write Digital' incorporates:
     *  Constant: '<S7>/Enable VoltPAQ-X2,X4'
     */

    /* S-Function Block: q_srv02_lab2_mdl/SRV02-ET Speed/SRV02-ET/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      q_srv02_lab2_mdl_DW.HILWriteDigital_Buffer[0] =
        (q_srv02_lab2_mdl_P.EnableVoltPAQX2X4_Value[0] != 0);
      q_srv02_lab2_mdl_DW.HILWriteDigital_Buffer[1] =
        (q_srv02_lab2_mdl_P.EnableVoltPAQX2X4_Value[1] != 0);
      q_srv02_lab2_mdl_DW.HILWriteDigital_Buffer[2] =
        (q_srv02_lab2_mdl_P.EnableVoltPAQX2X4_Value[2] != 0);
      q_srv02_lab2_mdl_DW.HILWriteDigital_Buffer[3] =
        (q_srv02_lab2_mdl_P.EnableVoltPAQX2X4_Value[3] != 0);
      result = hil_write_digital(q_srv02_lab2_mdl_DW.HILInitialize_Card,
        q_srv02_lab2_mdl_P.HILWriteDigital_channels, 4,
        &q_srv02_lab2_mdl_DW.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      }
    }
  }

  /* TransferFcn: '<S4>/Transfer Fcn' */
  q_srv02_lab2_mdl_B.TransferFcn = 0.0;
  q_srv02_lab2_mdl_B.TransferFcn += q_srv02_lab2_mdl_P.TransferFcn_C *
    q_srv02_lab2_mdl_X.TransferFcn_CSTATE;
  if (rtmIsMajorTimeStep(q_srv02_lab2_mdl_M)) {
  }

  /* Gain: '<S6>/Inverse Amplifier  Gain (V//V)' */
  temp = 1.0 / q_srv02_lab2_mdl_P.K_AMP;

  /* Gain: '<S6>/Inverse Amplifier  Gain (V//V)' */
  q_srv02_lab2_mdl_B.InverseAmplifierGainVV_l = temp * q_srv02_lab2_mdl_B.Vi;

  /* Saturate: '<S6>/DACB Saturation (V)' */
  temp = -q_srv02_lab2_mdl_P.VMAX_DAC;
  u0 = q_srv02_lab2_mdl_B.InverseAmplifierGainVV_l;
  u2 = q_srv02_lab2_mdl_P.VMAX_DAC;
  if (u0 > u2) {
    /* Saturate: '<S6>/DACB Saturation (V)' */
    q_srv02_lab2_mdl_B.DACBSaturationV_l = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S6>/DACB Saturation (V)' */
    q_srv02_lab2_mdl_B.DACBSaturationV_l = temp;
  } else {
    /* Saturate: '<S6>/DACB Saturation (V)' */
    q_srv02_lab2_mdl_B.DACBSaturationV_l = u0;
  }

  /* End of Saturate: '<S6>/DACB Saturation (V)' */

  /* Gain: '<S6>/Amplifier  Gain (V//V)' */
  q_srv02_lab2_mdl_B.AmplifierGainVV_k = q_srv02_lab2_mdl_P.K_AMP *
    q_srv02_lab2_mdl_B.DACBSaturationV_l;

  /* Saturate: '<S6>/Amplifier  Saturation (V)' */
  temp = -q_srv02_lab2_mdl_P.VMAX_AMP;
  u0 = q_srv02_lab2_mdl_B.AmplifierGainVV_k;
  u2 = q_srv02_lab2_mdl_P.VMAX_AMP;
  if (u0 > u2) {
    /* Saturate: '<S6>/Amplifier  Saturation (V)' */
    q_srv02_lab2_mdl_B.AmplifierSaturationV_c = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S6>/Amplifier  Saturation (V)' */
    q_srv02_lab2_mdl_B.AmplifierSaturationV_c = temp;
  } else {
    /* Saturate: '<S6>/Amplifier  Saturation (V)' */
    q_srv02_lab2_mdl_B.AmplifierSaturationV_c = u0;
  }

  /* End of Saturate: '<S6>/Amplifier  Saturation (V)' */

  /* Integrator: '<S4>/Vel to Pos' */
  q_srv02_lab2_mdl_B.VeltoPos = q_srv02_lab2_mdl_X.VeltoPos_CSTATE;
}

/* Model update function */
void q_srv02_lab2_mdl_update(void)
{
  if (rtmIsMajorTimeStep(q_srv02_lab2_mdl_M)) {
    rt_ertODEUpdateContinuousStates(&q_srv02_lab2_mdl_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++q_srv02_lab2_mdl_M->Timing.clockTick0)) {
    ++q_srv02_lab2_mdl_M->Timing.clockTickH0;
  }

  q_srv02_lab2_mdl_M->Timing.t[0] = rtsiGetSolverStopTime
    (&q_srv02_lab2_mdl_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++q_srv02_lab2_mdl_M->Timing.clockTick1)) {
      ++q_srv02_lab2_mdl_M->Timing.clockTickH1;
    }

    q_srv02_lab2_mdl_M->Timing.t[1] = q_srv02_lab2_mdl_M->Timing.clockTick1 *
      q_srv02_lab2_mdl_M->Timing.stepSize1 +
      q_srv02_lab2_mdl_M->Timing.clockTickH1 *
      q_srv02_lab2_mdl_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void q_srv02_lab2_mdl_derivatives(void)
{
  XDot_q_srv02_lab2_mdl_T *_rtXdot;
  _rtXdot = ((XDot_q_srv02_lab2_mdl_T *) q_srv02_lab2_mdl_M->derivs);

  /* Derivatives for TransferFcn: '<S7>/Encoder High-Pass Filter' */
  _rtXdot->EncoderHighPassFilter_CSTATE[0] = 0.0;
  _rtXdot->EncoderHighPassFilter_CSTATE[0] +=
    q_srv02_lab2_mdl_P.EncoderHighPassFilter_A[0] *
    q_srv02_lab2_mdl_X.EncoderHighPassFilter_CSTATE[0];
  _rtXdot->EncoderHighPassFilter_CSTATE[1] = 0.0;
  _rtXdot->EncoderHighPassFilter_CSTATE[0] +=
    q_srv02_lab2_mdl_P.EncoderHighPassFilter_A[1] *
    q_srv02_lab2_mdl_X.EncoderHighPassFilter_CSTATE[1];
  _rtXdot->EncoderHighPassFilter_CSTATE[1] +=
    q_srv02_lab2_mdl_X.EncoderHighPassFilter_CSTATE[0];
  _rtXdot->EncoderHighPassFilter_CSTATE[0] +=
    q_srv02_lab2_mdl_B.EncoderCalibrationradcount;

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += q_srv02_lab2_mdl_P.TransferFcn_A *
    q_srv02_lab2_mdl_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += q_srv02_lab2_mdl_B.AmplifierSaturationV_c;

  /* Derivatives for Integrator: '<S4>/Vel to Pos' */
  _rtXdot->VeltoPos_CSTATE = q_srv02_lab2_mdl_B.TransferFcn;
}

/* Model initialize function */
void q_srv02_lab2_mdl_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S7>/HIL Initialize' */

  /* S-Function Block: q_srv02_lab2_mdl/SRV02-ET Speed/SRV02-ET/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &q_srv02_lab2_mdl_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (q_srv02_lab2_mdl_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(q_srv02_lab2_mdl_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      return;
    }

    if ((q_srv02_lab2_mdl_P.HILInitialize_AIPStart && !is_switching) ||
        (q_srv02_lab2_mdl_P.HILInitialize_AIPEnter && is_switching)) {
      q_srv02_lab2_mdl_DW.HILInitialize_AIMinimums[0] =
        (q_srv02_lab2_mdl_P.HILInitialize_AILow);
      q_srv02_lab2_mdl_DW.HILInitialize_AIMinimums[1] =
        (q_srv02_lab2_mdl_P.HILInitialize_AILow);
      q_srv02_lab2_mdl_DW.HILInitialize_AIMaximums[0] =
        q_srv02_lab2_mdl_P.HILInitialize_AIHigh;
      q_srv02_lab2_mdl_DW.HILInitialize_AIMaximums[1] =
        q_srv02_lab2_mdl_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (q_srv02_lab2_mdl_DW.HILInitialize_Card,
         q_srv02_lab2_mdl_P.HILInitialize_AIChannels, 2U,
         &q_srv02_lab2_mdl_DW.HILInitialize_AIMinimums[0],
         &q_srv02_lab2_mdl_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
        return;
      }
    }

    if ((q_srv02_lab2_mdl_P.HILInitialize_AOPStart && !is_switching) ||
        (q_srv02_lab2_mdl_P.HILInitialize_AOPEnter && is_switching)) {
      q_srv02_lab2_mdl_DW.HILInitialize_AOMinimums[0] =
        (q_srv02_lab2_mdl_P.HILInitialize_AOLow);
      q_srv02_lab2_mdl_DW.HILInitialize_AOMinimums[1] =
        (q_srv02_lab2_mdl_P.HILInitialize_AOLow);
      q_srv02_lab2_mdl_DW.HILInitialize_AOMaximums[0] =
        q_srv02_lab2_mdl_P.HILInitialize_AOHigh;
      q_srv02_lab2_mdl_DW.HILInitialize_AOMaximums[1] =
        q_srv02_lab2_mdl_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (q_srv02_lab2_mdl_DW.HILInitialize_Card,
         q_srv02_lab2_mdl_P.HILInitialize_AOChannels, 2U,
         &q_srv02_lab2_mdl_DW.HILInitialize_AOMinimums[0],
         &q_srv02_lab2_mdl_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
        return;
      }
    }

    if ((q_srv02_lab2_mdl_P.HILInitialize_AOStart && !is_switching) ||
        (q_srv02_lab2_mdl_P.HILInitialize_AOEnter && is_switching)) {
      q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[0] =
        q_srv02_lab2_mdl_P.HILInitialize_AOInitial;
      q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[1] =
        q_srv02_lab2_mdl_P.HILInitialize_AOInitial;
      result = hil_write_analog(q_srv02_lab2_mdl_DW.HILInitialize_Card,
        q_srv02_lab2_mdl_P.HILInitialize_AOChannels, 2U,
        &q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
        return;
      }
    }

    if (q_srv02_lab2_mdl_P.HILInitialize_AOReset) {
      q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[0] =
        q_srv02_lab2_mdl_P.HILInitialize_AOWatchdog;
      q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[1] =
        q_srv02_lab2_mdl_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (q_srv02_lab2_mdl_DW.HILInitialize_Card,
         q_srv02_lab2_mdl_P.HILInitialize_AOChannels, 2U,
         &q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
        return;
      }
    }

    if ((q_srv02_lab2_mdl_P.HILInitialize_EIPStart && !is_switching) ||
        (q_srv02_lab2_mdl_P.HILInitialize_EIPEnter && is_switching)) {
      q_srv02_lab2_mdl_DW.HILInitialize_QuadratureModes[0] =
        q_srv02_lab2_mdl_P.HILInitialize_EIQuadrature;
      q_srv02_lab2_mdl_DW.HILInitialize_QuadratureModes[1] =
        q_srv02_lab2_mdl_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (q_srv02_lab2_mdl_DW.HILInitialize_Card,
         q_srv02_lab2_mdl_P.HILInitialize_EIChannels, 2U,
         (t_encoder_quadrature_mode *)
         &q_srv02_lab2_mdl_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
        return;
      }
    }

    if ((q_srv02_lab2_mdl_P.HILInitialize_EIStart && !is_switching) ||
        (q_srv02_lab2_mdl_P.HILInitialize_EIEnter && is_switching)) {
      q_srv02_lab2_mdl_DW.HILInitialize_InitialEICounts[0] =
        q_srv02_lab2_mdl_P.HILInitialize_EIInitial;
      q_srv02_lab2_mdl_DW.HILInitialize_InitialEICounts[1] =
        q_srv02_lab2_mdl_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(q_srv02_lab2_mdl_DW.HILInitialize_Card,
        q_srv02_lab2_mdl_P.HILInitialize_EIChannels, 2U,
        &q_srv02_lab2_mdl_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_analog_timebase_block): '<S7>/HIL Read Analog Timebase' */

  /* S-Function Block: q_srv02_lab2_mdl/SRV02-ET Speed/SRV02-ET/HIL Read Analog Timebase (hil_read_analog_timebase_block) */
  {
    t_error result;
    result = hil_task_create_analog_reader
      (q_srv02_lab2_mdl_DW.HILInitialize_Card,
       q_srv02_lab2_mdl_P.HILReadAnalogTimebase_SamplesIn,
       q_srv02_lab2_mdl_P.HILReadAnalogTimebase_Channels, 2,
       &q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Task, (t_buffer_overflow_mode)
         (q_srv02_lab2_mdl_P.HILReadAnalogTimebase_OverflowM - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
    }
  }

  /* InitializeConditions for TransferFcn: '<S7>/Encoder High-Pass Filter' */
  q_srv02_lab2_mdl_X.EncoderHighPassFilter_CSTATE[0] = 0.0;
  q_srv02_lab2_mdl_X.EncoderHighPassFilter_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Transfer Fcn' */
  q_srv02_lab2_mdl_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Vel to Pos' */
  q_srv02_lab2_mdl_X.VeltoPos_CSTATE = q_srv02_lab2_mdl_P.VeltoPos_IC;
}

/* Model terminate function */
void q_srv02_lab2_mdl_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S7>/HIL Initialize' */

  /* S-Function Block: q_srv02_lab2_mdl/SRV02-ET Speed/SRV02-ET/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(q_srv02_lab2_mdl_DW.HILInitialize_Card);
    hil_monitor_stop_all(q_srv02_lab2_mdl_DW.HILInitialize_Card);
    is_switching = false;
    if ((q_srv02_lab2_mdl_P.HILInitialize_AOTerminate && !is_switching) ||
        (q_srv02_lab2_mdl_P.HILInitialize_AOExit && is_switching)) {
      q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[0] =
        q_srv02_lab2_mdl_P.HILInitialize_AOFinal;
      q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[1] =
        q_srv02_lab2_mdl_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(q_srv02_lab2_mdl_DW.HILInitialize_Card,
        q_srv02_lab2_mdl_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_srv02_lab2_mdl_M, _rt_error_message);
      }
    }

    hil_task_delete_all(q_srv02_lab2_mdl_DW.HILInitialize_Card);
    hil_monitor_delete_all(q_srv02_lab2_mdl_DW.HILInitialize_Card);
    hil_close(q_srv02_lab2_mdl_DW.HILInitialize_Card);
    q_srv02_lab2_mdl_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  q_srv02_lab2_mdl_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_srv02_lab2_mdl_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  q_srv02_lab2_mdl_initialize();
}

void MdlTerminate(void)
{
  q_srv02_lab2_mdl_terminate();
}

/* Registration function */
RT_MODEL_q_srv02_lab2_mdl_T *q_srv02_lab2_mdl(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_srv02_lab2_mdl_M, 0,
                sizeof(RT_MODEL_q_srv02_lab2_mdl_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&q_srv02_lab2_mdl_M->solverInfo,
                          &q_srv02_lab2_mdl_M->Timing.simTimeStep);
    rtsiSetTPtr(&q_srv02_lab2_mdl_M->solverInfo, &rtmGetTPtr(q_srv02_lab2_mdl_M));
    rtsiSetStepSizePtr(&q_srv02_lab2_mdl_M->solverInfo,
                       &q_srv02_lab2_mdl_M->Timing.stepSize0);
    rtsiSetdXPtr(&q_srv02_lab2_mdl_M->solverInfo, &q_srv02_lab2_mdl_M->derivs);
    rtsiSetContStatesPtr(&q_srv02_lab2_mdl_M->solverInfo, (real_T **)
                         &q_srv02_lab2_mdl_M->contStates);
    rtsiSetNumContStatesPtr(&q_srv02_lab2_mdl_M->solverInfo,
      &q_srv02_lab2_mdl_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&q_srv02_lab2_mdl_M->solverInfo,
      &q_srv02_lab2_mdl_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&q_srv02_lab2_mdl_M->solverInfo,
      &q_srv02_lab2_mdl_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&q_srv02_lab2_mdl_M->solverInfo,
      &q_srv02_lab2_mdl_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&q_srv02_lab2_mdl_M->solverInfo, (&rtmGetErrorStatus
      (q_srv02_lab2_mdl_M)));
    rtsiSetRTModelPtr(&q_srv02_lab2_mdl_M->solverInfo, q_srv02_lab2_mdl_M);
  }

  rtsiSetSimTimeStep(&q_srv02_lab2_mdl_M->solverInfo, MAJOR_TIME_STEP);
  q_srv02_lab2_mdl_M->intgData.f[0] = q_srv02_lab2_mdl_M->odeF[0];
  q_srv02_lab2_mdl_M->contStates = ((real_T *) &q_srv02_lab2_mdl_X);
  rtsiSetSolverData(&q_srv02_lab2_mdl_M->solverInfo, (void *)
                    &q_srv02_lab2_mdl_M->intgData);
  rtsiSetSolverName(&q_srv02_lab2_mdl_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = q_srv02_lab2_mdl_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    q_srv02_lab2_mdl_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_srv02_lab2_mdl_M->Timing.sampleTimes =
      (&q_srv02_lab2_mdl_M->Timing.sampleTimesArray[0]);
    q_srv02_lab2_mdl_M->Timing.offsetTimes =
      (&q_srv02_lab2_mdl_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_srv02_lab2_mdl_M->Timing.sampleTimes[0] = (0.0);
    q_srv02_lab2_mdl_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    q_srv02_lab2_mdl_M->Timing.offsetTimes[0] = (0.0);
    q_srv02_lab2_mdl_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(q_srv02_lab2_mdl_M, &q_srv02_lab2_mdl_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = q_srv02_lab2_mdl_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    q_srv02_lab2_mdl_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_srv02_lab2_mdl_M, 5.0);
  q_srv02_lab2_mdl_M->Timing.stepSize0 = 0.001;
  q_srv02_lab2_mdl_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  q_srv02_lab2_mdl_M->Sizes.checksums[0] = (545695585U);
  q_srv02_lab2_mdl_M->Sizes.checksums[1] = (4236165226U);
  q_srv02_lab2_mdl_M->Sizes.checksums[2] = (3640529314U);
  q_srv02_lab2_mdl_M->Sizes.checksums[3] = (489935565U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    q_srv02_lab2_mdl_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(q_srv02_lab2_mdl_M->extModeInfo,
      &q_srv02_lab2_mdl_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_srv02_lab2_mdl_M->extModeInfo,
                        q_srv02_lab2_mdl_M->Sizes.checksums);
    rteiSetTPtr(q_srv02_lab2_mdl_M->extModeInfo, rtmGetTPtr(q_srv02_lab2_mdl_M));
  }

  q_srv02_lab2_mdl_M->solverInfoPtr = (&q_srv02_lab2_mdl_M->solverInfo);
  q_srv02_lab2_mdl_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&q_srv02_lab2_mdl_M->solverInfo, 0.001);
  rtsiSetSolverMode(&q_srv02_lab2_mdl_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_srv02_lab2_mdl_M->blockIO = ((void *) &q_srv02_lab2_mdl_B);

  {
    q_srv02_lab2_mdl_B.HILReadAnalogTimebase_o1 = 0.0;
    q_srv02_lab2_mdl_B.HILReadAnalogTimebase_o2 = 0.0;
    q_srv02_lab2_mdl_B.HILReadEncoder = 0.0;
    q_srv02_lab2_mdl_B.EncoderCalibrationradcount = 0.0;
    q_srv02_lab2_mdl_B.EncoderHighPassFilter = 0.0;
    q_srv02_lab2_mdl_B.PositionSourceSwitch = 0.0;
    q_srv02_lab2_mdl_B.TachometerCalibrationradsV = 0.0;
    q_srv02_lab2_mdl_B.VelocitySourceSwitch = 0.0;
    q_srv02_lab2_mdl_B.SignalGenerator = 0.0;
    q_srv02_lab2_mdl_B.SliderGain = 0.0;
    q_srv02_lab2_mdl_B.SliderGain_h = 0.0;
    q_srv02_lab2_mdl_B.Vi = 0.0;
    q_srv02_lab2_mdl_B.DirectionConventionRightHandsys = 0.0;
    q_srv02_lab2_mdl_B.AmplifierSaturationV = 0.0;
    q_srv02_lab2_mdl_B.InverseAmplifierGainVV = 0.0;
    q_srv02_lab2_mdl_B.DACBSaturationV = 0.0;
    q_srv02_lab2_mdl_B.AmplifierGainVV = 0.0;
    q_srv02_lab2_mdl_B.TransferFcn = 0.0;
    q_srv02_lab2_mdl_B.InverseAmplifierGainVV_l = 0.0;
    q_srv02_lab2_mdl_B.DACBSaturationV_l = 0.0;
    q_srv02_lab2_mdl_B.AmplifierGainVV_k = 0.0;
    q_srv02_lab2_mdl_B.AmplifierSaturationV_c = 0.0;
    q_srv02_lab2_mdl_B.VeltoPos = 0.0;
    q_srv02_lab2_mdl_B.PotentiometerCalibrationradV = 0.0;
  }

  /* parameters */
  q_srv02_lab2_mdl_M->defaultParam = ((real_T *)&q_srv02_lab2_mdl_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &q_srv02_lab2_mdl_X;
    q_srv02_lab2_mdl_M->contStates = (x);
    (void) memset((void *)&q_srv02_lab2_mdl_X, 0,
                  sizeof(X_q_srv02_lab2_mdl_T));
  }

  /* states (dwork) */
  q_srv02_lab2_mdl_M->dwork = ((void *) &q_srv02_lab2_mdl_DW);
  (void) memset((void *)&q_srv02_lab2_mdl_DW, 0,
                sizeof(DW_q_srv02_lab2_mdl_T));
  q_srv02_lab2_mdl_DW.HILInitialize_AIMinimums[0] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AIMinimums[1] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AIMaximums[0] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AIMaximums[1] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AOMinimums[0] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AOMinimums[1] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AOMaximums[0] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AOMaximums[1] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[0] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_AOVoltages[1] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_FilterFrequency[0] = 0.0;
  q_srv02_lab2_mdl_DW.HILInitialize_FilterFrequency[1] = 0.0;
  q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Buffer[0] = 0.0;
  q_srv02_lab2_mdl_DW.HILReadAnalogTimebase_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_srv02_lab2_mdl_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_srv02_lab2_mdl_M->Sizes.numContStates = (4);/* Number of continuous states */
  q_srv02_lab2_mdl_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  q_srv02_lab2_mdl_M->Sizes.numY = (0);/* Number of model outputs */
  q_srv02_lab2_mdl_M->Sizes.numU = (0);/* Number of model inputs */
  q_srv02_lab2_mdl_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_srv02_lab2_mdl_M->Sizes.numSampTimes = (2);/* Number of sample times */
  q_srv02_lab2_mdl_M->Sizes.numBlocks = (33);/* Number of blocks */
  q_srv02_lab2_mdl_M->Sizes.numBlockIO = (24);/* Number of block outputs */
  q_srv02_lab2_mdl_M->Sizes.numBlockPrms = (101);/* Sum of parameter "widths" */
  return q_srv02_lab2_mdl_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
