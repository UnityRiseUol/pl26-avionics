//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: INS_Model_C.cpp
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
#include "rtwtypes.h"
#include <cmath>
#include "INS_Model_C_private.h"
#include "cmath"
#include <cfloat>

//
// Output and update for atomic system:
//    '<S57>/SqrtUsedFcn'
//    '<S273>/SqrtUsedFcn'
//    '<S327>/SqrtUsedFcn'
//
void INS_Model_C::INS_Model_C_SqrtUsedFcn(real_T rtu_u, boolean_T rtu_isSqrtUsed,
  real_T *rty_P)
{
  if (rtu_isSqrtUsed) {
    *rty_P = rtu_u * rtu_u;
  } else {
    *rty_P = rtu_u;
  }
}

//
// Disable for enable system:
//    '<S28>/MeasurementUpdate'
//    '<S244>/MeasurementUpdate'
//    '<S298>/MeasurementUpdate'
//
void INS_Model_C::INS_M_MeasurementUpdate_Disable(real_T *rty_Lykyhatkk1,
  DW_MeasurementUpdate_INS_Mode_T *localDW)
{
  // Outputs for Enabled SubSystem: '<S28>/MeasurementUpdate' incorporates:
  //   EnablePort: '<S59>/Enable'

  // Disable for Outport: '<S59>/L*(y[k]-yhat[k|k-1])'
  *rty_Lykyhatkk1 = 0.0;

  // End of Outputs for SubSystem: '<S28>/MeasurementUpdate'
  localDW->MeasurementUpdate_MODE = false;
}

//
// Output and update for enable system:
//    '<S28>/MeasurementUpdate'
//    '<S244>/MeasurementUpdate'
//    '<S298>/MeasurementUpdate'
//
void INS_Model_C::INS_Model_C_MeasurementUpdate(boolean_T rtu_Enable, real_T
  rtu_Lk, real_T rtu_yk, real_T rtu_Ck, real_T rtu_xhatkk1, real_T
  *rty_Lykyhatkk1, const ConstB_MeasurementUpdate_INS__T *localC,
  DW_MeasurementUpdate_INS_Mode_T *localDW)
{
  // Outputs for Enabled SubSystem: '<S28>/MeasurementUpdate' incorporates:
  //   EnablePort: '<S59>/Enable'

  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    // Product: '<S59>/Product3' incorporates:
    //   Product: '<S59>/C[k]*xhat[k|k-1]'
    //   Sum: '<S59>/Add1'
    //   Sum: '<S59>/Sum'

    *rty_Lykyhatkk1 = (rtu_yk - (rtu_Ck * rtu_xhatkk1 + localC->Dkuk)) * rtu_Lk;
  } else if (localDW->MeasurementUpdate_MODE) {
    INS_M_MeasurementUpdate_Disable(rty_Lykyhatkk1, localDW);
  }

  // End of Outputs for SubSystem: '<S28>/MeasurementUpdate'
}

//
// Disable for enable system:
//    '<S35>/Enabled Subsystem'
//    '<S251>/Enabled Subsystem'
//    '<S305>/Enabled Subsystem'
//
void INS_Model_C::INS_Mo_EnabledSubsystem_Disable(real_T *rty_deltax,
  DW_EnabledSubsystem_INS_Model_T *localDW)
{
  // Outputs for Enabled SubSystem: '<S35>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S61>/Enable'

  // Disable for Outport: '<S61>/deltax'
  *rty_deltax = 0.0;

  // End of Outputs for SubSystem: '<S35>/Enabled Subsystem'
  localDW->EnabledSubsystem_MODE = false;
}

//
// Output and update for enable system:
//    '<S35>/Enabled Subsystem'
//    '<S251>/Enabled Subsystem'
//    '<S305>/Enabled Subsystem'
//
void INS_Model_C::INS_Model_C_EnabledSubsystem(boolean_T rtu_Enable, real_T
  rtu_Mk, real_T rtu_Ck, real_T rtu_yk, real_T rtu_xhatkk1, real_T *rty_deltax,
  DW_EnabledSubsystem_INS_Model_T *localDW)
{
  // Outputs for Enabled SubSystem: '<S35>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S61>/Enable'

  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    // Product: '<S61>/Product2' incorporates:
    //   Product: '<S61>/Product'
    //   Sum: '<S61>/Add1'

    *rty_deltax = (rtu_yk - rtu_Ck * rtu_xhatkk1) * rtu_Mk;
  } else if (localDW->EnabledSubsystem_MODE) {
    INS_Mo_EnabledSubsystem_Disable(rty_deltax, localDW);
  }

  // End of Outputs for SubSystem: '<S35>/Enabled Subsystem'
}

//
// Output and update for atomic system:
//    '<S111>/SqrtUsedFcn'
//    '<S165>/SqrtUsedFcn'
//    '<S219>/SqrtUsedFcn'
//
void INS_Model_C::INS_Model_C_SqrtUsedFcn_h(const real_T rtu_u[9], boolean_T
  rtu_isSqrtUsed, real_T rty_P[9])
{
  if (rtu_isSqrtUsed) {
    for (int32_T i{0}; i < 3; i++) {
      for (int32_T i_0{0}; i_0 < 3; i_0++) {
        rty_P[i + 3 * i_0] = (rtu_u[i + 3] * rtu_u[i_0 + 3] + rtu_u[i] *
                              rtu_u[i_0]) + rtu_u[i + 6] * rtu_u[i_0 + 6];
      }
    }
  } else {
    for (int32_T i{0}; i < 3; i++) {
      for (int32_T i_0{0}; i_0 < 3; i_0++) {
        rty_P[i + 3 * i_0] = rtu_u[3 * i_0 + i];
      }
    }
  }
}

//
// Disable for enable system:
//    '<S82>/MeasurementUpdate'
//    '<S136>/MeasurementUpdate'
//    '<S190>/MeasurementUpdate'
//
void INS_Model_C::INS_MeasurementUpdate_b_Disable(real_T rty_Lykyhatkk1[3],
  DW_MeasurementUpdate_INS_Mo_f_T *localDW)
{
  // Outputs for Enabled SubSystem: '<S82>/MeasurementUpdate' incorporates:
  //   EnablePort: '<S113>/Enable'

  // Disable for Outport: '<S113>/L*(y[k]-yhat[k|k-1])'
  rty_Lykyhatkk1[0] = 0.0;
  rty_Lykyhatkk1[1] = 0.0;
  rty_Lykyhatkk1[2] = 0.0;

  // End of Outputs for SubSystem: '<S82>/MeasurementUpdate'
  localDW->MeasurementUpdate_MODE = false;
}

//
// Output and update for enable system:
//    '<S82>/MeasurementUpdate'
//    '<S136>/MeasurementUpdate'
//    '<S190>/MeasurementUpdate'
//
void INS_Model_C::INS_Model_C_MeasurementUpdate_d(boolean_T rtu_Enable, const
  real_T rtu_Lk[3], real_T rtu_yk, const real_T rtu_Ck[3], const real_T
  rtu_xhatkk1[3], real_T rtu_Dk, real_T rtu_uk, real_T rty_Lykyhatkk1[3],
  DW_MeasurementUpdate_INS_Mo_f_T *localDW)
{
  real_T rtb_Sum_n;

  // Outputs for Enabled SubSystem: '<S82>/MeasurementUpdate' incorporates:
  //   EnablePort: '<S113>/Enable'

  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    // Sum: '<S113>/Sum' incorporates:
    //   Product: '<S113>/C[k]*xhat[k|k-1]'
    //   Product: '<S113>/D[k]*u[k]'
    //   Sum: '<S113>/Add1'

    rtb_Sum_n = rtu_yk - (((rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] *
      rtu_xhatkk1[1]) + rtu_Ck[2] * rtu_xhatkk1[2]) + rtu_Dk * rtu_uk);

    // Product: '<S113>/Product3'
    rty_Lykyhatkk1[0] = rtu_Lk[0] * rtb_Sum_n;
    rty_Lykyhatkk1[1] = rtu_Lk[1] * rtb_Sum_n;
    rty_Lykyhatkk1[2] = rtu_Lk[2] * rtb_Sum_n;
  } else if (localDW->MeasurementUpdate_MODE) {
    INS_MeasurementUpdate_b_Disable(rty_Lykyhatkk1, localDW);
  }

  // End of Outputs for SubSystem: '<S82>/MeasurementUpdate'
}

//
// Disable for enable system:
//    '<S89>/Enabled Subsystem'
//    '<S143>/Enabled Subsystem'
//    '<S197>/Enabled Subsystem'
//
void INS_Model_C::INS__EnabledSubsystem_h_Disable(real_T rty_deltax[3],
  DW_EnabledSubsystem_INS_Mod_i_T *localDW)
{
  // Outputs for Enabled SubSystem: '<S89>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S115>/Enable'

  // Disable for Outport: '<S115>/deltax'
  rty_deltax[0] = 0.0;
  rty_deltax[1] = 0.0;
  rty_deltax[2] = 0.0;

  // End of Outputs for SubSystem: '<S89>/Enabled Subsystem'
  localDW->EnabledSubsystem_MODE = false;
}

//
// Output and update for enable system:
//    '<S89>/Enabled Subsystem'
//    '<S143>/Enabled Subsystem'
//    '<S197>/Enabled Subsystem'
//
void INS_Model_C::INS_Model_C_EnabledSubsystem_j(boolean_T rtu_Enable, const
  real_T rtu_Mk[3], const real_T rtu_Ck[3], real_T rtu_yk, const real_T
  rtu_xhatkk1[3], real_T rty_deltax[3], DW_EnabledSubsystem_INS_Mod_i_T *localDW)
{
  real_T rtb_Add1_h;

  // Outputs for Enabled SubSystem: '<S89>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S115>/Enable'

  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    // Sum: '<S115>/Add1' incorporates:
    //   Product: '<S115>/Product'

    rtb_Add1_h = rtu_yk - ((rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] *
      rtu_xhatkk1[1]) + rtu_Ck[2] * rtu_xhatkk1[2]);

    // Product: '<S115>/Product2'
    rty_deltax[0] = rtu_Mk[0] * rtb_Add1_h;
    rty_deltax[1] = rtu_Mk[1] * rtb_Add1_h;
    rty_deltax[2] = rtu_Mk[2] * rtb_Add1_h;
  } else if (localDW->EnabledSubsystem_MODE) {
    INS__EnabledSubsystem_h_Disable(rty_deltax, localDW);
  }

  // End of Outputs for SubSystem: '<S89>/Enabled Subsystem'
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (std::isinf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = std::fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > std::floor(u1))) {
      real_T q;
      q = std::abs(u0 / u1);
      yEq = !(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = (rtNaN);
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    real_T q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }

  return y;
}

// Model step function
void INS_Model_C::step()
{
  real_T rtb_P_mi[9];
  real_T DiscreteTimeIntegrator_idx_1;
  real_T DiscreteTimeIntegrator_idx_2;
  real_T flat;
  real_T refLat;
  real_T rtb_Add_f;
  real_T rtb_Add_m;
  real_T rtb_Akxhatkk1_n;
  real_T rtb_LLAtoFlatEarth_idx_0;
  real_T rtb_LLAtoFlatEarth_idx_1;
  real_T rtb_LLAtoFlatEarth_idx_2;
  real_T rtb_Product1_a;
  real_T rtb_Product2_e;
  real_T rtb_Product3_l;
  real_T rtb_Product_l;
  real_T rtb_Sum_tmp;
  real_T rtb_Sum_tmp_0;
  real_T rtb_Sum_tmp_1;
  int32_T i;

  // Delay: '<S4>/MemoryX' incorporates:
  //   Constant: '<S4>/X0'

  if (INS_Model_C_DW.icLoad) {
    INS_Model_C_DW.MemoryX_DSTATE[0] = 0.0;
    INS_Model_C_DW.MemoryX_DSTATE[1] = 0.0;
    INS_Model_C_DW.MemoryX_DSTATE[2] = 0.0;
  }

  // LLA2Flat: '<Root>/LLA to Flat Earth' incorporates:
  //   Gain: '<Root>/Gain1'
  //   Inport: '<Root>/BMP_Altitude'
  //   Inport: '<Root>/GPS_LL'
  //   Inport: '<Root>/LL_ref'
  //   Inport: '<Root>/h_ref'

  refLat = INS_Model_C_U.LL_ref[0] * 3.1415926535897931 / 180.0;
  rtb_Product3_l = INS_Model_C_U.LL_ref[1] * 3.1415926535897931 / 180.0;
  flat = std::abs(refLat);
  if (flat > 3.1415926535897931) {
    refLat = rt_modd_snf(refLat + 3.1415926535897931, 6.2831853071795862) -
      3.1415926535897931;
    flat = std::abs(refLat);
  }

  if (flat > 1.5707963267948966) {
    rtb_Product3_l += 3.1415926535897931;
    if (std::isnan(refLat)) {
      rtb_Add_f = (rtNaN);
    } else if (refLat < 0.0) {
      rtb_Add_f = -1.0;
    } else {
      rtb_Add_f = (refLat > 0.0);
    }

    refLat = (1.5707963267948966 - (flat - 1.5707963267948966)) * rtb_Add_f;
  }

  if (std::abs(rtb_Product3_l) > 3.1415926535897931) {
    rtb_Product2_e = rt_remd_snf(rtb_Product3_l, 6.2831853071795862);
    rtb_Product3_l = rtb_Product2_e - std::trunc(rtb_Product2_e /
      3.1415926535897931) * 6.2831853071795862;
  }

  flat = std::abs(INS_Model_C_U.GPS_LL[0] * 3.1415926535897931 / 180.0);
  rtb_LLAtoFlatEarth_idx_0 = INS_Model_C_U.GPS_LL[0] * 3.1415926535897931 /
    180.0;
  rtb_Product2_e = INS_Model_C_U.GPS_LL[1] * 3.1415926535897931 / 180.0;
  if (flat > 3.1415926535897931) {
    rtb_LLAtoFlatEarth_idx_0 = rt_modd_snf(INS_Model_C_U.GPS_LL[0] *
      3.1415926535897931 / 180.0 + 3.1415926535897931, 6.2831853071795862) -
      3.1415926535897931;
    flat = std::abs(rtb_LLAtoFlatEarth_idx_0);
  }

  if (flat > 1.5707963267948966) {
    rtb_Product2_e = INS_Model_C_U.GPS_LL[1] * 3.1415926535897931 / 180.0 +
      3.1415926535897931;
    if (std::isnan(rtb_LLAtoFlatEarth_idx_0)) {
      rtb_Add_f = (rtNaN);
    } else if (rtb_LLAtoFlatEarth_idx_0 < 0.0) {
      rtb_Add_f = -1.0;
    } else {
      rtb_Add_f = (rtb_LLAtoFlatEarth_idx_0 > 0.0);
    }

    rtb_LLAtoFlatEarth_idx_0 = (1.5707963267948966 - (flat - 1.5707963267948966))
      * rtb_Add_f;
  }

  if (std::abs(rtb_Product2_e) > 3.1415926535897931) {
    rtb_Product2_e = rt_remd_snf(rtb_Product2_e, 6.2831853071795862);
    rtb_Product2_e -= std::trunc(rtb_Product2_e / 3.1415926535897931) *
      6.2831853071795862;
  }

  rtb_Add_f = rtb_LLAtoFlatEarth_idx_0 - refLat;
  flat = std::abs(rtb_Add_f);
  rtb_Product2_e -= rtb_Product3_l;
  if (flat > 3.1415926535897931) {
    rtb_Add_f = rt_modd_snf(rtb_Add_f + 3.1415926535897931, 6.2831853071795862)
      - 3.1415926535897931;
    flat = std::abs(rtb_Add_f);
  }

  if (flat > 1.5707963267948966) {
    rtb_Product2_e += 3.1415926535897931;
    if (std::isnan(rtb_Add_f)) {
      rtb_Add_f = (rtNaN);
    } else if (rtb_Add_f < 0.0) {
      rtb_Add_f = -1.0;
    } else {
      rtb_Add_f = (rtb_Add_f > 0.0);
    }

    rtb_Add_f *= 1.5707963267948966 - (flat - 1.5707963267948966);
  }

  if (std::abs(rtb_Product2_e) > 3.1415926535897931) {
    rtb_Product2_e = rt_remd_snf(rtb_Product2_e, 6.2831853071795862);
    rtb_Product2_e -= std::trunc(rtb_Product2_e / 3.1415926535897931) *
      6.2831853071795862;
  }

  rtb_LLAtoFlatEarth_idx_0 = std::sin(refLat);
  rtb_LLAtoFlatEarth_idx_0 = 1.0 - 0.00669437999014133 *
    rtb_LLAtoFlatEarth_idx_0 * rtb_LLAtoFlatEarth_idx_0;
  rtb_LLAtoFlatEarth_idx_1 = 6.378137E+6 / std::sqrt(rtb_LLAtoFlatEarth_idx_0);
  rtb_LLAtoFlatEarth_idx_2 = rtb_LLAtoFlatEarth_idx_1 * std::cos(refLat) *
    rtb_Product2_e;
  rtb_LLAtoFlatEarth_idx_1 = rtb_LLAtoFlatEarth_idx_1 * 0.99664718933525254 *
    0.99664718933525254 / rtb_LLAtoFlatEarth_idx_0 * rtb_Add_f;
  rtb_LLAtoFlatEarth_idx_0 = rtb_LLAtoFlatEarth_idx_2 * 0.0 +
    rtb_LLAtoFlatEarth_idx_1;
  rtb_LLAtoFlatEarth_idx_1 = rtb_LLAtoFlatEarth_idx_2 - rtb_LLAtoFlatEarth_idx_1
    * 0.0;
  rtb_LLAtoFlatEarth_idx_2 = -(-INS_Model_C_U.BMP_Altitude + INS_Model_C_U.h_ref);

  // End of LLA2Flat: '<Root>/LLA to Flat Earth'

  // Delay: '<S1>/MemoryX' incorporates:
  //   Constant: '<S1>/X0'

  if (INS_Model_C_DW.icLoad_i) {
    INS_Model_C_DW.MemoryX_DSTATE_i = 0.0;
  }

  // Outputs for Enabled SubSystem: '<S35>/Enabled Subsystem'
  // Constant: '<S1>/Enable' incorporates:
  //   Constant: '<S1>/C'
  //   Constant: '<S8>/KalmanGainM'
  //   Delay: '<S1>/MemoryX'
  //   Inport: '<Root>/BNO_Lin_Accel'

  INS_Model_C_EnabledSubsystem(true, 0.1674399363528013, 1.0,
    INS_Model_C_U.BNO_Lin_Accel[0], INS_Model_C_DW.MemoryX_DSTATE_i,
    &INS_Model_C_B.Product2_a, &INS_Model_C_DW.EnabledSubsystem);

  // End of Outputs for SubSystem: '<S35>/Enabled Subsystem'

  // Sum: '<S35>/Add' incorporates:
  //   Delay: '<S1>/MemoryX'

  rtb_Add_f = INS_Model_C_B.Product2_a + INS_Model_C_DW.MemoryX_DSTATE_i;

  // Sqrt: '<S336>/sqrt' incorporates:
  //   Inport: '<Root>/BNO_Quaternion'
  //   Product: '<S337>/Product'
  //   Product: '<S337>/Product1'
  //   Product: '<S337>/Product2'
  //   Product: '<S337>/Product3'
  //   Sum: '<S337>/Sum'

  rtb_Product_l = std::sqrt(((INS_Model_C_U.BNO_Quaternion[0] *
    INS_Model_C_U.BNO_Quaternion[0] + INS_Model_C_U.BNO_Quaternion[1] *
    INS_Model_C_U.BNO_Quaternion[1]) + INS_Model_C_U.BNO_Quaternion[2] *
    INS_Model_C_U.BNO_Quaternion[2]) + INS_Model_C_U.BNO_Quaternion[3] *
    INS_Model_C_U.BNO_Quaternion[3]);

  // Product: '<S332>/Product2' incorporates:
  //   Inport: '<Root>/BNO_Quaternion'

  rtb_Product2_e = INS_Model_C_U.BNO_Quaternion[2] / rtb_Product_l;

  // Product: '<S332>/Product3' incorporates:
  //   Inport: '<Root>/BNO_Quaternion'

  rtb_Product3_l = INS_Model_C_U.BNO_Quaternion[3] / rtb_Product_l;

  // Product: '<S332>/Product1' incorporates:
  //   Inport: '<Root>/BNO_Quaternion'

  rtb_Product1_a = INS_Model_C_U.BNO_Quaternion[1] / rtb_Product_l;

  // Product: '<S332>/Product' incorporates:
  //   Inport: '<Root>/BNO_Quaternion'

  rtb_Product_l = INS_Model_C_U.BNO_Quaternion[0] / rtb_Product_l;

  // Delay: '<S5>/MemoryX' incorporates:
  //   Constant: '<S5>/X0'

  if (INS_Model_C_DW.icLoad_d) {
    INS_Model_C_DW.MemoryX_DSTATE_g = 0.0;
  }

  // Outputs for Enabled SubSystem: '<S251>/Enabled Subsystem'
  // Constant: '<S5>/Enable' incorporates:
  //   Constant: '<S224>/KalmanGainM'
  //   Constant: '<S5>/C'
  //   Delay: '<S5>/MemoryX'
  //   Inport: '<Root>/BNO_Lin_Accel'

  INS_Model_C_EnabledSubsystem(true, 0.1674399363528013, 1.0,
    INS_Model_C_U.BNO_Lin_Accel[1], INS_Model_C_DW.MemoryX_DSTATE_g,
    &INS_Model_C_B.Product2_h, &INS_Model_C_DW.EnabledSubsystem_e);

  // End of Outputs for SubSystem: '<S251>/Enabled Subsystem'

  // Sum: '<S251>/Add' incorporates:
  //   Delay: '<S5>/MemoryX'

  rtb_Add_m = INS_Model_C_B.Product2_h + INS_Model_C_DW.MemoryX_DSTATE_g;

  // Delay: '<S6>/MemoryX' incorporates:
  //   Constant: '<S6>/X0'

  if (INS_Model_C_DW.icLoad_p) {
    INS_Model_C_DW.MemoryX_DSTATE_e = 0.0;
  }

  // Outputs for Enabled SubSystem: '<S305>/Enabled Subsystem'
  // Constant: '<S6>/Enable' incorporates:
  //   Constant: '<S278>/KalmanGainM'
  //   Constant: '<S6>/C'
  //   Delay: '<S6>/MemoryX'
  //   Inport: '<Root>/BNO_Lin_Accel'

  INS_Model_C_EnabledSubsystem(true, 0.1674399363528013, 1.0,
    INS_Model_C_U.BNO_Lin_Accel[2], INS_Model_C_DW.MemoryX_DSTATE_e,
    &INS_Model_C_B.Product2, &INS_Model_C_DW.EnabledSubsystem_g);

  // End of Outputs for SubSystem: '<S305>/Enabled Subsystem'

  // Sum: '<S305>/Add' incorporates:
  //   Delay: '<S6>/MemoryX'

  rtb_Akxhatkk1_n = INS_Model_C_B.Product2 + INS_Model_C_DW.MemoryX_DSTATE_e;

  // Product: '<S333>/Product7' incorporates:
  //   Product: '<S334>/Product7'

  rtb_Sum_tmp = rtb_Product3_l * rtb_Product3_l;

  // Product: '<S333>/Product' incorporates:
  //   Product: '<S334>/Product'

  DiscreteTimeIntegrator_idx_1 = rtb_Product1_a * rtb_Product2_e;

  // Product: '<S333>/Product1' incorporates:
  //   Product: '<S334>/Product1'

  refLat = rtb_Product_l * rtb_Product3_l;

  // Product: '<S333>/Product3' incorporates:
  //   Product: '<S335>/Product'

  rtb_Sum_tmp_0 = rtb_Product1_a * rtb_Product3_l;

  // Product: '<S333>/Product2' incorporates:
  //   Product: '<S335>/Product1'

  DiscreteTimeIntegrator_idx_2 = rtb_Product_l * rtb_Product2_e;

  // Product: '<S333>/Product6' incorporates:
  //   Product: '<S335>/Product7'

  rtb_Sum_tmp_1 = rtb_Product2_e * rtb_Product2_e;

  // Product: '<S334>/Product3' incorporates:
  //   Product: '<S335>/Product3'

  rtb_Product2_e *= rtb_Product3_l;

  // Product: '<S334>/Product2' incorporates:
  //   Product: '<S335>/Product2'

  rtb_Product3_l = rtb_Product_l * rtb_Product1_a;

  // Sum: '<S334>/Sum3' incorporates:
  //   Constant: '<S334>/Constant'
  //   Product: '<S334>/Product6'
  //   Sum: '<S335>/Sum3'

  flat = 0.5 - rtb_Product1_a * rtb_Product1_a;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
  //   Constant: '<S333>/Constant'
  //   Gain: '<S333>/Gain'
  //   Gain: '<S333>/Gain1'
  //   Gain: '<S333>/Gain2'
  //   Product: '<S333>/Product'
  //   Product: '<S333>/Product1'
  //   Product: '<S333>/Product2'
  //   Product: '<S333>/Product3'
  //   Product: '<S333>/Product4'
  //   Product: '<S333>/Product5'
  //   Product: '<S333>/Product6'
  //   Product: '<S333>/Product7'
  //   Product: '<S333>/Product8'
  //   Sum: '<S333>/Sum'
  //   Sum: '<S333>/Sum1'
  //   Sum: '<S333>/Sum2'
  //   Sum: '<S333>/Sum3'

  rtb_Product1_a = ((((0.5 - rtb_Sum_tmp_1) - rtb_Sum_tmp) * 2.0 * rtb_Add_f +
                     (DiscreteTimeIntegrator_idx_1 + refLat) * 2.0 * rtb_Add_m)
                    + (rtb_Sum_tmp_0 - DiscreteTimeIntegrator_idx_2) * 2.0 *
                    rtb_Akxhatkk1_n) * 0.005;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  rtb_Product_l = rtb_Product1_a + INS_Model_C_DW.DiscreteTimeIntegrator_DSTATE
    [0];

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S334>/Gain'
  //   Gain: '<S334>/Gain1'
  //   Gain: '<S334>/Gain2'
  //   Product: '<S334>/Product2'
  //   Product: '<S334>/Product3'
  //   Product: '<S334>/Product4'
  //   Product: '<S334>/Product5'
  //   Product: '<S334>/Product8'
  //   Sum: '<S334>/Sum'
  //   Sum: '<S334>/Sum1'
  //   Sum: '<S334>/Sum2'
  //   Sum: '<S334>/Sum3'

  rtb_Sum_tmp = (((flat - rtb_Sum_tmp) * 2.0 * rtb_Add_m +
                  (DiscreteTimeIntegrator_idx_1 - refLat) * 2.0 * rtb_Add_f) +
                 (rtb_Product3_l + rtb_Product2_e) * 2.0 * rtb_Akxhatkk1_n) *
    0.005;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  DiscreteTimeIntegrator_idx_1 = rtb_Sum_tmp +
    INS_Model_C_DW.DiscreteTimeIntegrator_DSTATE[1];

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
  //   Gain: '<S335>/Gain'
  //   Gain: '<S335>/Gain1'
  //   Gain: '<S335>/Gain2'
  //   Product: '<S335>/Product4'
  //   Product: '<S335>/Product5'
  //   Product: '<S335>/Product8'
  //   Sum: '<S335>/Sum'
  //   Sum: '<S335>/Sum1'
  //   Sum: '<S335>/Sum2'
  //   Sum: '<S335>/Sum3'

  rtb_Sum_tmp_0 = (((rtb_Sum_tmp_0 + DiscreteTimeIntegrator_idx_2) * 2.0 *
                    rtb_Add_f + (rtb_Product2_e - rtb_Product3_l) * 2.0 *
                    rtb_Add_m) + (flat - rtb_Sum_tmp_1) * 2.0 * rtb_Akxhatkk1_n)
    * 0.005;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  DiscreteTimeIntegrator_idx_2 = rtb_Sum_tmp_0 +
    INS_Model_C_DW.DiscreteTimeIntegrator_DSTATE[2];

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  rtb_Sum_tmp_1 = 0.005 * rtb_Product_l;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[0] += rtb_Sum_tmp_1;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  rtb_Akxhatkk1_n = 0.005 * DiscreteTimeIntegrator_idx_1;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[1] += rtb_Akxhatkk1_n;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  rtb_Add_m = 0.005 * DiscreteTimeIntegrator_idx_2;

  // DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[2] += rtb_Add_m;

  // Outputs for Enabled SubSystem: '<S190>/MeasurementUpdate'
  // Constant: '<S4>/Enable' incorporates:
  //   Constant: '<S170>/KalmanGainL'
  //   Constant: '<S4>/C'
  //   Constant: '<S4>/D'
  //   Delay: '<S4>/MemoryX'

  INS_Model_C_MeasurementUpdate_d(true, INS_Model_C_ConstP.KalmanGainL_Value,
    INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[2], INS_Model_C_ConstP.pooled8,
    INS_Model_C_DW.MemoryX_DSTATE, 0.0, rtb_LLAtoFlatEarth_idx_2,
    INS_Model_C_B.Product3_k, &INS_Model_C_DW.MeasurementUpdate_n);

  // End of Outputs for SubSystem: '<S190>/MeasurementUpdate'

  // Delay: '<S2>/MemoryX' incorporates:
  //   Constant: '<S2>/X0'

  if (INS_Model_C_DW.icLoad_g) {
    INS_Model_C_DW.MemoryX_DSTATE_b[0] = 0.0;
    INS_Model_C_DW.MemoryX_DSTATE_b[1] = 0.0;
    INS_Model_C_DW.MemoryX_DSTATE_b[2] = 0.0;
  }

  // Outputs for Enabled SubSystem: '<S89>/Enabled Subsystem'
  // Constant: '<S2>/Enable' incorporates:
  //   Constant: '<S2>/C'
  //   Constant: '<S62>/KalmanGainM'
  //   Delay: '<S2>/MemoryX'

  INS_Model_C_EnabledSubsystem_j(true, INS_Model_C_ConstP.pooled11,
    INS_Model_C_ConstP.pooled8, INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[0],
    INS_Model_C_DW.MemoryX_DSTATE_b, INS_Model_C_B.Product2_f,
    &INS_Model_C_DW.EnabledSubsystem_j);

  // End of Outputs for SubSystem: '<S89>/Enabled Subsystem'

  // Outport: '<Root>/X_Estimate' incorporates:
  //   Delay: '<S2>/MemoryX'
  //   Sum: '<S89>/Add'

  INS_Model_C_Y.X_Estimate = INS_Model_C_B.Product2_f[2] +
    INS_Model_C_DW.MemoryX_DSTATE_b[2];

  // Delay: '<S3>/MemoryX' incorporates:
  //   Constant: '<S3>/X0'

  if (INS_Model_C_DW.icLoad_j) {
    INS_Model_C_DW.MemoryX_DSTATE_el[0] = 0.0;
    INS_Model_C_DW.MemoryX_DSTATE_el[1] = 0.0;
    INS_Model_C_DW.MemoryX_DSTATE_el[2] = 0.0;
  }

  // Outputs for Enabled SubSystem: '<S143>/Enabled Subsystem'
  // Constant: '<S3>/Enable' incorporates:
  //   Constant: '<S116>/KalmanGainM'
  //   Constant: '<S3>/C'
  //   Delay: '<S3>/MemoryX'

  INS_Model_C_EnabledSubsystem_j(true, INS_Model_C_ConstP.pooled11,
    INS_Model_C_ConstP.pooled8, INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[1],
    INS_Model_C_DW.MemoryX_DSTATE_el, INS_Model_C_B.Product2_o,
    &INS_Model_C_DW.EnabledSubsystem_d);

  // End of Outputs for SubSystem: '<S143>/Enabled Subsystem'

  // SignalConversion generated from: '<Root>/Flat Earth to LLA' incorporates:
  //   Delay: '<S3>/MemoryX'
  //   Sum: '<S143>/Add'

  INS_Model_C_Y.Y_Estimate = INS_Model_C_B.Product2_o[2] +
    INS_Model_C_DW.MemoryX_DSTATE_el[2];

  // Outputs for Enabled SubSystem: '<S197>/Enabled Subsystem'
  // Constant: '<S4>/Enable' incorporates:
  //   Constant: '<S170>/KalmanGainM'
  //   Constant: '<S4>/C'
  //   Delay: '<S4>/MemoryX'

  INS_Model_C_EnabledSubsystem_j(true, INS_Model_C_ConstP.KalmanGainM_Value,
    INS_Model_C_ConstP.pooled8, INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[2],
    INS_Model_C_DW.MemoryX_DSTATE, INS_Model_C_B.Product2_j,
    &INS_Model_C_DW.EnabledSubsystem_m);

  // End of Outputs for SubSystem: '<S197>/Enabled Subsystem'

  // Outport: '<Root>/Z_Estimate' incorporates:
  //   Delay: '<S4>/MemoryX'
  //   Sum: '<S197>/Add'

  INS_Model_C_Y.Z_Estimate = INS_Model_C_B.Product2_j[2] +
    INS_Model_C_DW.MemoryX_DSTATE[2];

  // Outputs for Enabled SubSystem: '<S136>/MeasurementUpdate'
  // Constant: '<S3>/Enable' incorporates:
  //   Constant: '<S116>/KalmanGainL'
  //   Constant: '<S3>/C'
  //   Constant: '<S3>/D'
  //   Delay: '<S3>/MemoryX'

  INS_Model_C_MeasurementUpdate_d(true, INS_Model_C_ConstP.pooled10,
    INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[1], INS_Model_C_ConstP.pooled8,
    INS_Model_C_DW.MemoryX_DSTATE_el, 0.0, rtb_LLAtoFlatEarth_idx_1,
    INS_Model_C_B.Product3_i, &INS_Model_C_DW.MeasurementUpdate_o);

  // End of Outputs for SubSystem: '<S136>/MeasurementUpdate'

  // Outputs for Enabled SubSystem: '<S82>/MeasurementUpdate'
  // Constant: '<S2>/Enable' incorporates:
  //   Constant: '<S2>/C'
  //   Constant: '<S2>/D'
  //   Constant: '<S62>/KalmanGainL'
  //   Delay: '<S2>/MemoryX'

  INS_Model_C_MeasurementUpdate_d(true, INS_Model_C_ConstP.pooled10,
    INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[0], INS_Model_C_ConstP.pooled8,
    INS_Model_C_DW.MemoryX_DSTATE_b, 0.0, rtb_LLAtoFlatEarth_idx_0,
    INS_Model_C_B.Product3_p, &INS_Model_C_DW.MeasurementUpdate_d);

  // End of Outputs for SubSystem: '<S82>/MeasurementUpdate'

  // FlatEarth2LLA: '<Root>/Flat Earth to LLA' incorporates:
  //   Inport: '<Root>/LL_ref'
  //   SignalConversion generated from: '<Root>/Flat Earth to LLA'

  refLat = INS_Model_C_U.LL_ref[0] * 3.1415926535897931 / 180.0;
  rtb_Product3_l = INS_Model_C_U.LL_ref[1] * 3.1415926535897931 / 180.0;
  flat = std::abs(refLat);
  if (flat > 3.1415926535897931) {
    refLat = rt_modd_snf(refLat + 3.1415926535897931, 6.2831853071795862) -
      3.1415926535897931;
    flat = std::abs(refLat);
  }

  if (flat > 1.5707963267948966) {
    rtb_Product3_l += 3.1415926535897931;
    if (std::isnan(refLat)) {
      rtb_Add_f = (rtNaN);
    } else if (refLat < 0.0) {
      rtb_Add_f = -1.0;
    } else {
      rtb_Add_f = (refLat > 0.0);
    }

    refLat = (1.5707963267948966 - (flat - 1.5707963267948966)) * rtb_Add_f;
  }

  if (std::abs(rtb_Product3_l) > 3.1415926535897931) {
    rtb_Product2_e = rt_remd_snf(rtb_Product3_l, 6.2831853071795862);
    rtb_Product3_l = rtb_Product2_e - std::trunc(rtb_Product2_e /
      3.1415926535897931) * 6.2831853071795862;
  }

  rtb_Add_f = std::sin(refLat);
  rtb_Add_f = 1.0 - 0.00669437999014133 * rtb_Add_f * rtb_Add_f;
  rtb_Product2_e = 6.378137E+6 / std::sqrt(rtb_Add_f);
  rtb_Add_f = (INS_Model_C_Y.X_Estimate - 0.0 * INS_Model_C_Y.Y_Estimate) /
    (rtb_Product2_e * 0.99664718933525254 * 0.99664718933525254 / rtb_Add_f) +
    refLat;
  flat = std::abs(rtb_Add_f);
  rtb_Product2_e = (0.0 * INS_Model_C_Y.X_Estimate + INS_Model_C_Y.Y_Estimate) /
    (rtb_Product2_e * std::cos(refLat)) + rtb_Product3_l;
  if (flat > 3.1415926535897931) {
    rtb_Add_f = rt_modd_snf(rtb_Add_f + 3.1415926535897931, 6.2831853071795862)
      - 3.1415926535897931;
    flat = std::abs(rtb_Add_f);
  }

  if (flat > 1.5707963267948966) {
    rtb_Product2_e += 3.1415926535897931;
    if (std::isnan(rtb_Add_f)) {
      rtb_Add_f = (rtNaN);
    } else if (rtb_Add_f < 0.0) {
      rtb_Add_f = -1.0;
    } else {
      rtb_Add_f = (rtb_Add_f > 0.0);
    }

    rtb_Add_f *= 1.5707963267948966 - (flat - 1.5707963267948966);
  }

  if (std::abs(rtb_Product2_e) > 3.1415926535897931) {
    rtb_Product2_e = rt_remd_snf(rtb_Product2_e, 6.2831853071795862);
    rtb_Product2_e -= std::trunc(rtb_Product2_e / 3.1415926535897931) *
      6.2831853071795862;
  }

  // Outport: '<Root>/Lat_Estimate' incorporates:
  //   FlatEarth2LLA: '<Root>/Flat Earth to LLA'

  INS_Model_C_Y.Lat_Estimate = rtb_Add_f * 180.0 / 3.1415926535897931;

  // Outport: '<Root>/Long_Estimate' incorporates:
  //   FlatEarth2LLA: '<Root>/Flat Earth to LLA'

  INS_Model_C_Y.Long_Estimate = rtb_Product2_e * 180.0 / 3.1415926535897931;

  // Outputs for Enabled SubSystem: '<S298>/MeasurementUpdate'
  // Constant: '<S6>/Enable' incorporates:
  //   Constant: '<S278>/KalmanGainL'
  //   Constant: '<S6>/C'
  //   Delay: '<S6>/MemoryX'
  //   Inport: '<Root>/BNO_Lin_Accel'

  INS_Model_C_MeasurementUpdate(true, 0.15906793953516124,
    INS_Model_C_U.BNO_Lin_Accel[2], 1.0, INS_Model_C_DW.MemoryX_DSTATE_e,
    &INS_Model_C_B.Product3, &INS_Model_C_ConstB.MeasurementUpdate_c,
    &INS_Model_C_DW.MeasurementUpdate_c);

  // End of Outputs for SubSystem: '<S298>/MeasurementUpdate'

  // Outputs for Enabled SubSystem: '<S244>/MeasurementUpdate'
  // Constant: '<S5>/Enable' incorporates:
  //   Constant: '<S224>/KalmanGainL'
  //   Constant: '<S5>/C'
  //   Delay: '<S5>/MemoryX'
  //   Inport: '<Root>/BNO_Lin_Accel'

  INS_Model_C_MeasurementUpdate(true, 0.15906793953516124,
    INS_Model_C_U.BNO_Lin_Accel[1], 1.0, INS_Model_C_DW.MemoryX_DSTATE_g,
    &INS_Model_C_B.Product3_d, &INS_Model_C_ConstB.MeasurementUpdate_p,
    &INS_Model_C_DW.MeasurementUpdate_p);

  // End of Outputs for SubSystem: '<S244>/MeasurementUpdate'

  // Outputs for Enabled SubSystem: '<S28>/MeasurementUpdate'
  // Constant: '<S1>/Enable' incorporates:
  //   Constant: '<S1>/C'
  //   Constant: '<S8>/KalmanGainL'
  //   Delay: '<S1>/MemoryX'
  //   Inport: '<Root>/BNO_Lin_Accel'

  INS_Model_C_MeasurementUpdate(true, 0.15906793953516124,
    INS_Model_C_U.BNO_Lin_Accel[0], 1.0, INS_Model_C_DW.MemoryX_DSTATE_i,
    &INS_Model_C_B.Product3_k3, &INS_Model_C_ConstB.MeasurementUpdate,
    &INS_Model_C_DW.MeasurementUpdate);

  // End of Outputs for SubSystem: '<S28>/MeasurementUpdate'

  // MATLAB Function: '<S111>/SqrtUsedFcn' incorporates:
  //   Constant: '<S111>/isSqrtUsed'
  //   Constant: '<S62>/CovarianceZ'

  INS_Model_C_SqrtUsedFcn_h(INS_Model_C_ConstP.pooled9, false, rtb_P_mi);

  // MATLAB Function: '<S165>/SqrtUsedFcn' incorporates:
  //   Constant: '<S116>/CovarianceZ'
  //   Constant: '<S165>/isSqrtUsed'

  INS_Model_C_SqrtUsedFcn_h(INS_Model_C_ConstP.pooled9, false, rtb_P_mi);

  // MATLAB Function: '<S219>/SqrtUsedFcn' incorporates:
  //   Constant: '<S170>/CovarianceZ'
  //   Constant: '<S219>/isSqrtUsed'

  INS_Model_C_SqrtUsedFcn_h(INS_Model_C_ConstP.CovarianceZ_Value, false,
    rtb_P_mi);

  // MATLAB Function: '<S57>/SqrtUsedFcn' incorporates:
  //   Constant: '<S57>/isSqrtUsed'
  //   Constant: '<S8>/CovarianceZ'

  INS_Model_C_SqrtUsedFcn(0.1674399363528013, false, &rtb_Add_f);

  // MATLAB Function: '<S273>/SqrtUsedFcn' incorporates:
  //   Constant: '<S224>/CovarianceZ'
  //   Constant: '<S273>/isSqrtUsed'

  INS_Model_C_SqrtUsedFcn(0.1674399363528013, false, &rtb_Add_f);

  // MATLAB Function: '<S327>/SqrtUsedFcn' incorporates:
  //   Constant: '<S278>/CovarianceZ'
  //   Constant: '<S327>/isSqrtUsed'

  INS_Model_C_SqrtUsedFcn(0.1674399363528013, false, &rtb_Add_f);

  // Update for Delay: '<S4>/MemoryX'
  INS_Model_C_DW.icLoad = false;

  // Product: '<S190>/A[k]*xhat[k|k-1]'
  refLat = 0.0;
  rtb_Product2_e = 0.0;
  rtb_Product3_l = 0.0;

  // Update for Delay: '<S1>/MemoryX' incorporates:
  //   Constant: '<S1>/A'
  //   Product: '<S28>/A[k]*xhat[k|k-1]'
  //   Sum: '<S28>/Add'

  INS_Model_C_DW.icLoad_i = false;
  INS_Model_C_DW.MemoryX_DSTATE_i = (0.95 * INS_Model_C_DW.MemoryX_DSTATE_i +
    INS_Model_C_ConstB.Bkuk) + INS_Model_C_B.Product3_k3;

  // Update for Delay: '<S5>/MemoryX' incorporates:
  //   Constant: '<S5>/A'
  //   Product: '<S244>/A[k]*xhat[k|k-1]'
  //   Sum: '<S244>/Add'

  INS_Model_C_DW.icLoad_d = false;
  INS_Model_C_DW.MemoryX_DSTATE_g = (0.95 * INS_Model_C_DW.MemoryX_DSTATE_g +
    INS_Model_C_ConstB.Bkuk_o) + INS_Model_C_B.Product3_d;

  // Update for Delay: '<S6>/MemoryX' incorporates:
  //   Constant: '<S6>/A'
  //   Product: '<S298>/A[k]*xhat[k|k-1]'
  //   Sum: '<S298>/Add'

  INS_Model_C_DW.icLoad_p = false;
  INS_Model_C_DW.MemoryX_DSTATE_e = (0.95 * INS_Model_C_DW.MemoryX_DSTATE_e +
    INS_Model_C_ConstB.Bkuk_n) + INS_Model_C_B.Product3;

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
  INS_Model_C_DW.DiscreteTimeIntegrator_DSTATE[0] = rtb_Product1_a +
    rtb_Product_l;
  INS_Model_C_DW.DiscreteTimeIntegrator_DSTATE[1] = rtb_Sum_tmp +
    DiscreteTimeIntegrator_idx_1;
  INS_Model_C_DW.DiscreteTimeIntegrator_DSTATE[2] = rtb_Sum_tmp_0 +
    DiscreteTimeIntegrator_idx_2;

  // Update for Delay: '<S2>/MemoryX'
  INS_Model_C_DW.icLoad_g = false;

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[0] += rtb_Sum_tmp_1;

  // Product: '<S82>/A[k]*xhat[k|k-1]'
  rtb_Product1_a = 0.0;

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[1] += rtb_Akxhatkk1_n;

  // Product: '<S82>/A[k]*xhat[k|k-1]'
  rtb_Product_l = 0.0;

  // Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
  INS_Model_C_DW.DiscreteTimeIntegrator1_DSTATE[2] += rtb_Add_m;

  // Product: '<S82>/A[k]*xhat[k|k-1]'
  rtb_Sum_tmp = 0.0;

  // Update for Delay: '<S3>/MemoryX'
  INS_Model_C_DW.icLoad_j = false;

  // Product: '<S136>/A[k]*xhat[k|k-1]'
  DiscreteTimeIntegrator_idx_1 = 0.0;
  rtb_Add_m = 0.0;
  rtb_Akxhatkk1_n = 0.0;
  for (i = 0; i < 3; i++) {
    // Product: '<S190>/A[k]*xhat[k|k-1]' incorporates:
    //   Constant: '<S4>/A'
    //   Delay: '<S4>/MemoryX'

    rtb_Add_f = INS_Model_C_DW.MemoryX_DSTATE[i];
    rtb_Sum_tmp_0 = INS_Model_C_ConstP.pooled6[3 * i];
    refLat += rtb_Sum_tmp_0 * rtb_Add_f;
    DiscreteTimeIntegrator_idx_2 = INS_Model_C_ConstP.pooled6[3 * i + 1];
    rtb_Product2_e += DiscreteTimeIntegrator_idx_2 * rtb_Add_f;
    rtb_Sum_tmp_1 = INS_Model_C_ConstP.pooled6[3 * i + 2];
    rtb_Product3_l += rtb_Sum_tmp_1 * rtb_Add_f;

    // Product: '<S82>/A[k]*xhat[k|k-1]' incorporates:
    //   Constant: '<S2>/A'
    //   Delay: '<S2>/MemoryX'

    rtb_Add_f = INS_Model_C_DW.MemoryX_DSTATE_b[i];
    rtb_Product1_a += rtb_Sum_tmp_0 * rtb_Add_f;
    rtb_Product_l += DiscreteTimeIntegrator_idx_2 * rtb_Add_f;
    rtb_Sum_tmp += rtb_Sum_tmp_1 * rtb_Add_f;

    // Product: '<S136>/A[k]*xhat[k|k-1]' incorporates:
    //   Constant: '<S3>/A'
    //   Delay: '<S3>/MemoryX'

    rtb_Add_f = INS_Model_C_DW.MemoryX_DSTATE_el[i];
    DiscreteTimeIntegrator_idx_1 += rtb_Sum_tmp_0 * rtb_Add_f;
    rtb_Add_m += DiscreteTimeIntegrator_idx_2 * rtb_Add_f;
    rtb_Akxhatkk1_n += rtb_Sum_tmp_1 * rtb_Add_f;
  }

  // Update for Delay: '<S4>/MemoryX' incorporates:
  //   Constant: '<S4>/B'
  //   Product: '<S190>/B[k]*u[k]'
  //   Product: '<S221>/Product3'
  //   Sum: '<S190>/Add'

  INS_Model_C_DW.MemoryX_DSTATE[0] = (0.0002 * rtb_LLAtoFlatEarth_idx_2 + refLat)
    + INS_Model_C_B.Product3_k[0];
  INS_Model_C_DW.MemoryX_DSTATE[1] = (0.02 * rtb_LLAtoFlatEarth_idx_2 +
    rtb_Product2_e) + INS_Model_C_B.Product3_k[1];
  INS_Model_C_DW.MemoryX_DSTATE[2] = (0.0 * rtb_LLAtoFlatEarth_idx_2 +
    rtb_Product3_l) + INS_Model_C_B.Product3_k[2];

  // Update for Delay: '<S2>/MemoryX' incorporates:
  //   Constant: '<S2>/B'
  //   Product: '<S113>/Product3'
  //   Product: '<S82>/B[k]*u[k]'
  //   Sum: '<S82>/Add'

  INS_Model_C_DW.MemoryX_DSTATE_b[0] = (0.0002 * rtb_LLAtoFlatEarth_idx_0 +
    rtb_Product1_a) + INS_Model_C_B.Product3_p[0];
  INS_Model_C_DW.MemoryX_DSTATE_b[1] = (0.02 * rtb_LLAtoFlatEarth_idx_0 +
    rtb_Product_l) + INS_Model_C_B.Product3_p[1];
  INS_Model_C_DW.MemoryX_DSTATE_b[2] = (0.0 * rtb_LLAtoFlatEarth_idx_0 +
    rtb_Sum_tmp) + INS_Model_C_B.Product3_p[2];

  // Update for Delay: '<S3>/MemoryX' incorporates:
  //   Constant: '<S3>/B'
  //   Product: '<S136>/B[k]*u[k]'
  //   Product: '<S167>/Product3'
  //   Sum: '<S136>/Add'

  INS_Model_C_DW.MemoryX_DSTATE_el[0] = (0.0002 * rtb_LLAtoFlatEarth_idx_1 +
    DiscreteTimeIntegrator_idx_1) + INS_Model_C_B.Product3_i[0];
  INS_Model_C_DW.MemoryX_DSTATE_el[1] = (0.02 * rtb_LLAtoFlatEarth_idx_1 +
    rtb_Add_m) + INS_Model_C_B.Product3_i[1];
  INS_Model_C_DW.MemoryX_DSTATE_el[2] = (0.0 * rtb_LLAtoFlatEarth_idx_1 +
    rtb_Akxhatkk1_n) + INS_Model_C_B.Product3_i[2];
}

// Model initialize function
void INS_Model_C::initialize()
{
  // InitializeConditions for Delay: '<S4>/MemoryX'
  INS_Model_C_DW.icLoad = true;

  // InitializeConditions for Delay: '<S1>/MemoryX'
  INS_Model_C_DW.icLoad_i = true;

  // InitializeConditions for Delay: '<S5>/MemoryX'
  INS_Model_C_DW.icLoad_d = true;

  // InitializeConditions for Delay: '<S6>/MemoryX'
  INS_Model_C_DW.icLoad_p = true;

  // InitializeConditions for Delay: '<S2>/MemoryX'
  INS_Model_C_DW.icLoad_g = true;

  // InitializeConditions for Delay: '<S3>/MemoryX'
  INS_Model_C_DW.icLoad_j = true;
}

// Model terminate function
void INS_Model_C::terminate()
{
  // (no terminate code required)
}

const char_T* INS_Model_C::RT_MODEL_INS_Model_C_T::getErrorStatus() const
{
  return (errorStatus);
}

void INS_Model_C::RT_MODEL_INS_Model_C_T::setErrorStatus(const char_T* const
  volatile aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

// Constructor
INS_Model_C::INS_Model_C() :
  INS_Model_C_U(),
  INS_Model_C_Y(),
  INS_Model_C_B(),
  INS_Model_C_DW(),
  INS_Model_C_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
INS_Model_C::~INS_Model_C() = default;

// Real-Time Model get method
INS_Model_C::RT_MODEL_INS_Model_C_T * INS_Model_C::getRTM()
{
  return (&INS_Model_C_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
