//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: INS_Model_C_data.cpp
//
// Code generated for Simulink model 'INS_Model_C'.
//
// Model version                  : 2.0
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Feb  6 15:48:55 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "INS_Model_C.h"

// Invariant block signals (default storage)
const INS_Model_C::ConstB_INS_Model_C_T INS_Model_C_ConstB{
  0.0
  ,                                    // '<S28>/B[k]*u[k]'
  0.0
  ,                                    // '<S244>/B[k]*u[k]'
  0.0
  ,                                    // '<S298>/B[k]*u[k]'

  // Start of '<S298>/MeasurementUpdate'
  {
    0.0
    // '<S329>/D[k]*u[k]'
  }
  ,

  // End of '<S298>/MeasurementUpdate'

  // Start of '<S244>/MeasurementUpdate'
  {
    0.0
    // '<S275>/D[k]*u[k]'
  }
  ,

  // End of '<S244>/MeasurementUpdate'

  // Start of '<S28>/MeasurementUpdate'
  {
    0.0
    // '<S59>/D[k]*u[k]'
  }
  // End of '<S28>/MeasurementUpdate'
};

// Constant parameters (default storage)
const INS_Model_C::ConstP_INS_Model_C_T INS_Model_C_ConstP{
  // Pooled Parameter (Expression: pInitialization.A)
  //  Referenced by:
  //    '<S2>/A'
  //    '<S3>/A'
  //    '<S4>/A'

  { 1.0, 0.0, 0.0, 0.02, 1.0, 0.0, -0.0002, -0.02, 1.0 },

  // Pooled Parameter (Expression: pInitialization.C)
  //  Referenced by:
  //    '<S2>/C'
  //    '<S3>/C'
  //    '<S4>/C'

  { 1.0, 0.0, 0.0 },

  // Pooled Parameter (Expression: pInitialization.Z)
  //  Referenced by:
  //    '<S62>/CovarianceZ'
  //    '<S116>/CovarianceZ'

  { 0.31264236051297012, 0.85976632960405674, -0.082907034652501974,
    0.85976632960405674, 19.41414078416522, -1.833648365855479,
    -0.082907034652501987, -1.833648365855479, 5.1851229103041918 },

  // Pooled Parameter (Expression: pInitialization.L)
  //  Referenced by:
  //    '<S62>/KalmanGainL'
  //    '<S116>/KalmanGainL'

  { 0.3298542685119818, 0.86142447029710922, -0.082907034652499156 },

  // Pooled Parameter (Expression: pInitialization.M)
  //  Referenced by:
  //    '<S62>/KalmanGainM'
  //    '<S116>/KalmanGainM'

  { 0.31264236051297006, 0.85976632960405663, -0.082907034652501974 },

  // Expression: pInitialization.Z
  //  Referenced by: '<S170>/CovarianceZ'

  { 0.20856427489134743, 0.35545103866496197, -0.20355767022800053,
    0.35545103866496197, 87.725370433842784, -50.356678840710231,
    -0.20355767022800056, -50.356678840710231, 87.309664692768749 },

  // Expression: pInitialization.L
  //  Referenced by: '<S170>/KalmanGainL'

  { 0.86285602879476941, 1.4380887682780894, -0.814230680912037 },

  // Expression: pInitialization.M
  //  Referenced by: '<S170>/KalmanGainM'

  { 0.83425709956538974, 1.4218041546598479, -0.81423068091200224 }
};

//
// File trailer for generated code.
//
// [EOF]
//
