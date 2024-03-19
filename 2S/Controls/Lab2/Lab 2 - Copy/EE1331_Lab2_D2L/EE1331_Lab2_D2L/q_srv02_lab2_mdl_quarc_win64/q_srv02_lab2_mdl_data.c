/*
 * q_srv02_lab2_mdl_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_srv02_lab2_mdl".
 *
 * Model version              : 5.3
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Tue Feb  6 13:16:13 2024
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "q_srv02_lab2_mdl.h"
#include "q_srv02_lab2_mdl_private.h"

/* Block parameters (default storage) */
P_q_srv02_lab2_mdl_T q_srv02_lab2_mdl_P = {
  /* Variable: K_AMP
   * Referenced by:
   *   '<S6>/Amplifier  Gain (V//V)'
   *   '<S6>/Inverse Amplifier  Gain (V//V)'
   *   '<S8>/Amplifier  Gain (V//V)'
   *   '<S8>/Inverse Amplifier  Gain (V//V)'
   */
  1.0,

  /* Variable: K_ENC
   * Referenced by: '<S7>/Encoder Calibration  (rad//count)'
   */
  0.0015339807878856412,

  /* Variable: K_POT
   * Referenced by: '<S7>/Potentiometer Calibration  (rad//V)'
   */
  -0.614355896702004,

  /* Variable: K_TACH
   * Referenced by: '<S7>/Tachometer Calibration  (rad//s//V)'
   */
  -0.9973310011396167,

  /* Variable: VMAX_AMP
   * Referenced by:
   *   '<S6>/Amplifier  Saturation (V)'
   *   '<S8>/Amplifier  Saturation (V)'
   */
  24.0,

  /* Variable: VMAX_DAC
   * Referenced by:
   *   '<S6>/DACB Saturation (V)'
   *   '<S8>/DACB Saturation (V)'
   */
  10.0,

  /* Mask Parameter: AmplitudeV_gain
   * Referenced by: '<S1>/Slider Gain'
   */
  0.0,

  /* Mask Parameter: OffsetV_gain
   * Referenced by: '<S2>/Slider Gain'
   */
  1.0,

  /* Mask Parameter: HILReadEncoder_channels
   * Referenced by: '<S7>/HIL Read Encoder'
   */
  0U,

  /* Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S7>/HIL Write Analog'
   */
  0U,

  /* Mask Parameter: HILWriteDigital_channels
   * Referenced by: '<S7>/HIL Write Digital'
   */
  { 0U, 1U, 2U, 3U },

  /* Expression: set_other_outputs_at_terminate
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_out
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_start
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_in
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: final_analog_outputs
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: final_pwm_outputs
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: analog_input_maximums
   * Referenced by: '<S7>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_input_minimums
   * Referenced by: '<S7>/HIL Initialize'
   */
  -10.0,

  /* Expression: analog_output_maximums
   * Referenced by: '<S7>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_output_minimums
   * Referenced by: '<S7>/HIL Initialize'
   */
  -10.0,

  /* Expression: initial_analog_outputs
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_analog_outputs
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_frequency
   * Referenced by: '<S7>/HIL Initialize'
   */
  50.0,

  /* Expression: initial_pwm_outputs
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_pwm_outputs
   * Referenced by: '<S7>/HIL Initialize'
   */
  0.0,

  /* Computed Parameter: EncoderHighPassFilter_A
   * Referenced by: '<S7>/Encoder High-Pass Filter'
   */
  { -282.74333882308139, -24674.011002723397 },

  /* Computed Parameter: EncoderHighPassFilter_C
   * Referenced by: '<S7>/Encoder High-Pass Filter'
   */
  { 24674.011002723397, 0.0 },

  /* Expression: 2
   * Referenced by: '<S5>/Pos Src'
   */
  2.0,

  /* Expression: 1
   * Referenced by: '<Root>/Spd Src'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<Root>/Signal Generator'
   */
  1.0,

  /* Expression: 0.00000001
   * Referenced by: '<Root>/Signal Generator'
   */
  1.0E-8,

  /* Expression: 1
   * Referenced by: '<Root>/Constant'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S8>/Direction Convention: (Right-Hand) system'
   */
  -1.0,

  /* Expression: [1 1 1 1]
   * Referenced by: '<S7>/Enable VoltPAQ-X2,X4'
   */
  { 1.0, 1.0, 1.0, 1.0 },

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<S4>/Transfer Fcn'
   */
  -10.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<S4>/Transfer Fcn'
   */
  10.0,

  /* Expression: 0
   * Referenced by: '<S4>/Vel to Pos'
   */
  0.0,

  /* Computed Parameter: HILInitialize_CKChannels
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOWatchdog
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIInitial
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POModes
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILReadAnalogTimebase_Clock
   * Referenced by: '<S7>/HIL Read Analog Timebase'
   */
  0,

  /* Computed Parameter: HILInitialize_AIChannels
   * Referenced by: '<S7>/HIL Initialize'
   */
  { 0U, 1U },

  /* Computed Parameter: HILInitialize_AOChannels
   * Referenced by: '<S7>/HIL Initialize'
   */
  { 0U, 1U },

  /* Computed Parameter: HILInitialize_EIChannels
   * Referenced by: '<S7>/HIL Initialize'
   */
  { 0U, 1U },

  /* Computed Parameter: HILInitialize_EIQuadrature
   * Referenced by: '<S7>/HIL Initialize'
   */
  4U,

  /* Computed Parameter: HILReadAnalogTimebase_Channels
   * Referenced by: '<S7>/HIL Read Analog Timebase'
   */
  { 0U, 1U },

  /* Computed Parameter: HILReadAnalogTimebase_SamplesIn
   * Referenced by: '<S7>/HIL Read Analog Timebase'
   */
  1000U,

  /* Computed Parameter: HILInitialize_Active
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOTerminate
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOExit
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOTerminate
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOExit
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POTerminate
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POExit
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKPStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKPEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AIPStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AIPEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOPStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOPEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOReset
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOPStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOPEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOReset
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIPStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIPEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POPStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POPEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POStart
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POEnter
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POReset
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_OOReset
   * Referenced by: '<S7>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOFinal
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOInitial
   * Referenced by: '<S7>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILReadAnalogTimebase_Active
   * Referenced by: '<S7>/HIL Read Analog Timebase'
   */
  1,

  /* Computed Parameter: HILReadEncoder_Active
   * Referenced by: '<S7>/HIL Read Encoder'
   */
  1,

  /* Computed Parameter: HILWriteAnalog_Active
   * Referenced by: '<S7>/HIL Write Analog'
   */
  0,

  /* Computed Parameter: HILWriteDigital_Active
   * Referenced by: '<S7>/HIL Write Digital'
   */
  0,

  /* Computed Parameter: HILReadAnalogTimebase_OverflowM
   * Referenced by: '<S7>/HIL Read Analog Timebase'
   */
  1U
};
