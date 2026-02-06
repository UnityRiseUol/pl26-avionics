//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: INS_Model_C.h
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
#ifndef INS_Model_C_h_
#define INS_Model_C_h_
#include <cmath>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "INS_Model_C_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

// Class declaration for model INS_Model_C
class INS_Model_C final
{
  // public data and function members
 public:
  // Block states (default storage) for system '<S28>/MeasurementUpdate'
  struct DW_MeasurementUpdate_INS_Mode_T {
    boolean_T MeasurementUpdate_MODE;  // '<S28>/MeasurementUpdate'
  };

  // Block states (default storage) for system '<S35>/Enabled Subsystem'
  struct DW_EnabledSubsystem_INS_Model_T {
    boolean_T EnabledSubsystem_MODE;   // '<S35>/Enabled Subsystem'
  };

  // Block states (default storage) for system '<S82>/MeasurementUpdate'
  struct DW_MeasurementUpdate_INS_Mo_f_T {
    boolean_T MeasurementUpdate_MODE;  // '<S82>/MeasurementUpdate'
  };

  // Block states (default storage) for system '<S89>/Enabled Subsystem'
  struct DW_EnabledSubsystem_INS_Mod_i_T {
    boolean_T EnabledSubsystem_MODE;   // '<S89>/Enabled Subsystem'
  };

  // Block signals (default storage)
  struct B_INS_Model_C_T {
    real_T Product2;                   // '<S331>/Product2'
    real_T Product3;                   // '<S329>/Product3'
    real_T Product2_h;                 // '<S277>/Product2'
    real_T Product3_d;                 // '<S275>/Product3'
    real_T Product2_j[3];              // '<S223>/Product2'
    real_T Product3_k[3];              // '<S221>/Product3'
    real_T Product2_o[3];              // '<S169>/Product2'
    real_T Product3_i[3];              // '<S167>/Product3'
    real_T Product2_f[3];              // '<S115>/Product2'
    real_T Product3_p[3];              // '<S113>/Product3'
    real_T Product2_a;                 // '<S61>/Product2'
    real_T Product3_k3;                // '<S59>/Product3'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_INS_Model_C_T {
    real_T MemoryX_DSTATE[3];          // '<S4>/MemoryX'
    real_T MemoryX_DSTATE_i;           // '<S1>/MemoryX'
    real_T MemoryX_DSTATE_g;           // '<S5>/MemoryX'
    real_T MemoryX_DSTATE_e;           // '<S6>/MemoryX'
    real_T DiscreteTimeIntegrator_DSTATE[3];// '<Root>/Discrete-Time Integrator' 
    real_T DiscreteTimeIntegrator1_DSTATE[3];// '<Root>/Discrete-Time Integrator1' 
    real_T MemoryX_DSTATE_b[3];        // '<S2>/MemoryX'
    real_T MemoryX_DSTATE_el[3];       // '<S3>/MemoryX'
    boolean_T icLoad;                  // '<S4>/MemoryX'
    boolean_T icLoad_i;                // '<S1>/MemoryX'
    boolean_T icLoad_d;                // '<S5>/MemoryX'
    boolean_T icLoad_p;                // '<S6>/MemoryX'
    boolean_T icLoad_g;                // '<S2>/MemoryX'
    boolean_T icLoad_j;                // '<S3>/MemoryX'
    DW_EnabledSubsystem_INS_Model_T EnabledSubsystem_g;// '<S305>/Enabled Subsystem' 
    DW_MeasurementUpdate_INS_Mode_T MeasurementUpdate_c;// '<S298>/MeasurementUpdate' 
    DW_EnabledSubsystem_INS_Model_T EnabledSubsystem_e;// '<S251>/Enabled Subsystem' 
    DW_MeasurementUpdate_INS_Mode_T MeasurementUpdate_p;// '<S244>/MeasurementUpdate' 
    DW_EnabledSubsystem_INS_Mod_i_T EnabledSubsystem_m;// '<S197>/Enabled Subsystem' 
    DW_MeasurementUpdate_INS_Mo_f_T MeasurementUpdate_n;// '<S190>/MeasurementUpdate' 
    DW_EnabledSubsystem_INS_Mod_i_T EnabledSubsystem_d;// '<S143>/Enabled Subsystem' 
    DW_MeasurementUpdate_INS_Mo_f_T MeasurementUpdate_o;// '<S136>/MeasurementUpdate' 
    DW_EnabledSubsystem_INS_Mod_i_T EnabledSubsystem_j;// '<S89>/Enabled Subsystem' 
    DW_MeasurementUpdate_INS_Mo_f_T MeasurementUpdate_d;// '<S82>/MeasurementUpdate' 
    DW_EnabledSubsystem_INS_Model_T EnabledSubsystem;// '<S35>/Enabled Subsystem' 
    DW_MeasurementUpdate_INS_Mode_T MeasurementUpdate;// '<S28>/MeasurementUpdate' 
  };

  // Invariant block signals for system '<S28>/MeasurementUpdate'
  struct ConstB_MeasurementUpdate_INS__T {
    real_T Dkuk;                       // '<S59>/D[k]*u[k]'
  };

  // Invariant block signals (default storage)
  struct ConstB_INS_Model_C_T {
    real_T Bkuk;                       // '<S28>/B[k]*u[k]'
    real_T Bkuk_o;                     // '<S244>/B[k]*u[k]'
    real_T Bkuk_n;                     // '<S298>/B[k]*u[k]'
    ConstB_MeasurementUpdate_INS__T MeasurementUpdate_c;// '<S298>/MeasurementUpdate' 
    ConstB_MeasurementUpdate_INS__T MeasurementUpdate_p;// '<S244>/MeasurementUpdate' 
    ConstB_MeasurementUpdate_INS__T MeasurementUpdate;// '<S28>/MeasurementUpdate' 
  };

  // Constant parameters (default storage)
  struct ConstP_INS_Model_C_T {
    // Pooled Parameter (Expression: pInitialization.A)
    //  Referenced by:
    //    '<S2>/A'
    //    '<S3>/A'
    //    '<S4>/A'

    real_T pooled6[9];

    // Pooled Parameter (Expression: pInitialization.C)
    //  Referenced by:
    //    '<S2>/C'
    //    '<S3>/C'
    //    '<S4>/C'

    real_T pooled8[3];

    // Pooled Parameter (Expression: pInitialization.Z)
    //  Referenced by:
    //    '<S62>/CovarianceZ'
    //    '<S116>/CovarianceZ'

    real_T pooled9[9];

    // Pooled Parameter (Expression: pInitialization.L)
    //  Referenced by:
    //    '<S62>/KalmanGainL'
    //    '<S116>/KalmanGainL'

    real_T pooled10[3];

    // Pooled Parameter (Expression: pInitialization.M)
    //  Referenced by:
    //    '<S62>/KalmanGainM'
    //    '<S116>/KalmanGainM'

    real_T pooled11[3];

    // Expression: pInitialization.Z
    //  Referenced by: '<S170>/CovarianceZ'

    real_T CovarianceZ_Value[9];

    // Expression: pInitialization.L
    //  Referenced by: '<S170>/KalmanGainL'

    real_T KalmanGainL_Value[3];

    // Expression: pInitialization.M
    //  Referenced by: '<S170>/KalmanGainM'

    real_T KalmanGainM_Value[3];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_INS_Model_C_T {
    real_T GPS_LL[2];                  // '<Root>/GPS_LL'
    real_T BMP_Altitude;               // '<Root>/BMP_Altitude'
    real_T BNO_Quaternion[4];          // '<Root>/BNO_Quaternion'
    real_T BNO_Lin_Accel[3];           // '<Root>/BNO_Lin_Accel'
    real_T h_ref;                      // '<Root>/h_ref'
    real_T LL_ref[2];                  // '<Root>/LL_ref'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_INS_Model_C_T {
    real_T X_Estimate;                 // '<Root>/X_Estimate'
    real_T Y_Estimate;                 // '<Root>/Y_Estimate'
    real_T Z_Estimate;                 // '<Root>/Z_Estimate'
    real_T Lat_Estimate;               // '<Root>/Lat_Estimate'
    real_T Long_Estimate;              // '<Root>/Long_Estimate'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_INS_Model_C_T {
    const char_T * volatile errorStatus;
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const volatile aErrorStatus);
  };

  // Copy Constructor
  INS_Model_C(INS_Model_C const&) = delete;

  // Assignment Operator
  INS_Model_C& operator= (INS_Model_C const&) & = delete;

  // Move Constructor
  INS_Model_C(INS_Model_C &&) = delete;

  // Move Assignment Operator
  INS_Model_C& operator= (INS_Model_C &&) = delete;

  // Real-Time Model get method
  INS_Model_C::RT_MODEL_INS_Model_C_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_INS_Model_C_T *pExtU_INS_Model_C_T)
  {
    INS_Model_C_U = *pExtU_INS_Model_C_T;
  }

  // Root outports get method
  const ExtY_INS_Model_C_T &getExternalOutputs() const
  {
    return INS_Model_C_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  INS_Model_C();

  // Destructor
  ~INS_Model_C();

  // private data and function members
 private:
  // External inputs
  ExtU_INS_Model_C_T INS_Model_C_U;

  // External outputs
  ExtY_INS_Model_C_T INS_Model_C_Y;

  // Block signals
  B_INS_Model_C_T INS_Model_C_B;

  // Block states
  DW_INS_Model_C_T INS_Model_C_DW;

  // private member function(s) for subsystem '<S57>/SqrtUsedFcn'
  static void INS_Model_C_SqrtUsedFcn(real_T rtu_u, boolean_T rtu_isSqrtUsed,
    real_T *rty_P);

  // private member function(s) for subsystem '<S28>/MeasurementUpdate'
  static void INS_M_MeasurementUpdate_Disable(real_T *rty_Lykyhatkk1,
    DW_MeasurementUpdate_INS_Mode_T *localDW);
  void INS_Model_C_MeasurementUpdate(boolean_T rtu_Enable, real_T rtu_Lk, real_T
    rtu_yk, real_T rtu_Ck, real_T rtu_xhatkk1, real_T *rty_Lykyhatkk1, const
    ConstB_MeasurementUpdate_INS__T *localC, DW_MeasurementUpdate_INS_Mode_T
    *localDW);

  // private member function(s) for subsystem '<S35>/Enabled Subsystem'
  static void INS_Mo_EnabledSubsystem_Disable(real_T *rty_deltax,
    DW_EnabledSubsystem_INS_Model_T *localDW);
  void INS_Model_C_EnabledSubsystem(boolean_T rtu_Enable, real_T rtu_Mk, real_T
    rtu_Ck, real_T rtu_yk, real_T rtu_xhatkk1, real_T *rty_deltax,
    DW_EnabledSubsystem_INS_Model_T *localDW);

  // private member function(s) for subsystem '<S111>/SqrtUsedFcn'
  static void INS_Model_C_SqrtUsedFcn_h(const real_T rtu_u[9], boolean_T
    rtu_isSqrtUsed, real_T rty_P[9]);

  // private member function(s) for subsystem '<S82>/MeasurementUpdate'
  static void INS_MeasurementUpdate_b_Disable(real_T rty_Lykyhatkk1[3],
    DW_MeasurementUpdate_INS_Mo_f_T *localDW);
  void INS_Model_C_MeasurementUpdate_d(boolean_T rtu_Enable, const real_T
    rtu_Lk[3], real_T rtu_yk, const real_T rtu_Ck[3], const real_T rtu_xhatkk1[3],
    real_T rtu_Dk, real_T rtu_uk, real_T rty_Lykyhatkk1[3],
    DW_MeasurementUpdate_INS_Mo_f_T *localDW);

  // private member function(s) for subsystem '<S89>/Enabled Subsystem'
  static void INS__EnabledSubsystem_h_Disable(real_T rty_deltax[3],
    DW_EnabledSubsystem_INS_Mod_i_T *localDW);
  void INS_Model_C_EnabledSubsystem_j(boolean_T rtu_Enable, const real_T rtu_Mk
    [3], const real_T rtu_Ck[3], real_T rtu_yk, const real_T rtu_xhatkk1[3],
    real_T rty_deltax[3], DW_EnabledSubsystem_INS_Mod_i_T *localDW);

  // Real-Time Model
  RT_MODEL_INS_Model_C_T INS_Model_C_M;
};

extern const INS_Model_C::ConstB_INS_Model_C_T INS_Model_C_ConstB;// constant block i/o 

// Constant parameters (default storage)
extern const INS_Model_C::ConstP_INS_Model_C_T INS_Model_C_ConstP;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Display' : Unused code path elimination
//  Block '<S51>/Data Type Duplicate' : Unused code path elimination
//  Block '<S52>/Data Type Duplicate' : Unused code path elimination
//  Block '<S53>/Conversion' : Unused code path elimination
//  Block '<S53>/Data Type Duplicate' : Unused code path elimination
//  Block '<S54>/Data Type Duplicate' : Unused code path elimination
//  Block '<S11>/Data Type Duplicate' : Unused code path elimination
//  Block '<S12>/Data Type Duplicate' : Unused code path elimination
//  Block '<S13>/Data Type Duplicate' : Unused code path elimination
//  Block '<S14>/Data Type Duplicate' : Unused code path elimination
//  Block '<S16>/Data Type Duplicate' : Unused code path elimination
//  Block '<S17>/Data Type Duplicate' : Unused code path elimination
//  Block '<S18>/Data Type Duplicate' : Unused code path elimination
//  Block '<S19>/Conversion' : Unused code path elimination
//  Block '<S19>/Data Type Duplicate' : Unused code path elimination
//  Block '<S20>/Data Type Duplicate' : Unused code path elimination
//  Block '<S21>/Data Type Duplicate' : Unused code path elimination
//  Block '<S22>/Data Type Duplicate' : Unused code path elimination
//  Block '<S24>/Data Type Duplicate' : Unused code path elimination
//  Block '<S25>/Data Type Duplicate' : Unused code path elimination
//  Block '<S26>/Data Type Duplicate' : Unused code path elimination
//  Block '<S1>/G' : Unused code path elimination
//  Block '<S1>/H' : Unused code path elimination
//  Block '<S1>/N' : Unused code path elimination
//  Block '<S1>/P0' : Unused code path elimination
//  Block '<S1>/Q' : Unused code path elimination
//  Block '<S1>/R' : Unused code path elimination
//  Block '<S50>/CheckSignalProperties' : Unused code path elimination
//  Block '<S105>/Data Type Duplicate' : Unused code path elimination
//  Block '<S106>/Data Type Duplicate' : Unused code path elimination
//  Block '<S107>/Conversion' : Unused code path elimination
//  Block '<S107>/Data Type Duplicate' : Unused code path elimination
//  Block '<S108>/Data Type Duplicate' : Unused code path elimination
//  Block '<S65>/Data Type Duplicate' : Unused code path elimination
//  Block '<S66>/Data Type Duplicate' : Unused code path elimination
//  Block '<S67>/Data Type Duplicate' : Unused code path elimination
//  Block '<S68>/Data Type Duplicate' : Unused code path elimination
//  Block '<S70>/Data Type Duplicate' : Unused code path elimination
//  Block '<S71>/Data Type Duplicate' : Unused code path elimination
//  Block '<S72>/Data Type Duplicate' : Unused code path elimination
//  Block '<S73>/Conversion' : Unused code path elimination
//  Block '<S73>/Data Type Duplicate' : Unused code path elimination
//  Block '<S74>/Data Type Duplicate' : Unused code path elimination
//  Block '<S75>/Data Type Duplicate' : Unused code path elimination
//  Block '<S76>/Data Type Duplicate' : Unused code path elimination
//  Block '<S78>/Data Type Duplicate' : Unused code path elimination
//  Block '<S79>/Data Type Duplicate' : Unused code path elimination
//  Block '<S2>/G' : Unused code path elimination
//  Block '<S2>/H' : Unused code path elimination
//  Block '<S2>/N' : Unused code path elimination
//  Block '<S2>/P0' : Unused code path elimination
//  Block '<S2>/Q' : Unused code path elimination
//  Block '<S2>/R' : Unused code path elimination
//  Block '<S103>/CheckSignalProperties' : Unused code path elimination
//  Block '<S104>/CheckSignalProperties' : Unused code path elimination
//  Block '<S159>/Data Type Duplicate' : Unused code path elimination
//  Block '<S160>/Data Type Duplicate' : Unused code path elimination
//  Block '<S161>/Conversion' : Unused code path elimination
//  Block '<S161>/Data Type Duplicate' : Unused code path elimination
//  Block '<S162>/Data Type Duplicate' : Unused code path elimination
//  Block '<S119>/Data Type Duplicate' : Unused code path elimination
//  Block '<S120>/Data Type Duplicate' : Unused code path elimination
//  Block '<S121>/Data Type Duplicate' : Unused code path elimination
//  Block '<S122>/Data Type Duplicate' : Unused code path elimination
//  Block '<S124>/Data Type Duplicate' : Unused code path elimination
//  Block '<S125>/Data Type Duplicate' : Unused code path elimination
//  Block '<S126>/Data Type Duplicate' : Unused code path elimination
//  Block '<S127>/Conversion' : Unused code path elimination
//  Block '<S127>/Data Type Duplicate' : Unused code path elimination
//  Block '<S128>/Data Type Duplicate' : Unused code path elimination
//  Block '<S129>/Data Type Duplicate' : Unused code path elimination
//  Block '<S130>/Data Type Duplicate' : Unused code path elimination
//  Block '<S132>/Data Type Duplicate' : Unused code path elimination
//  Block '<S133>/Data Type Duplicate' : Unused code path elimination
//  Block '<S3>/G' : Unused code path elimination
//  Block '<S3>/H' : Unused code path elimination
//  Block '<S3>/N' : Unused code path elimination
//  Block '<S3>/P0' : Unused code path elimination
//  Block '<S3>/Q' : Unused code path elimination
//  Block '<S3>/R' : Unused code path elimination
//  Block '<S157>/CheckSignalProperties' : Unused code path elimination
//  Block '<S158>/CheckSignalProperties' : Unused code path elimination
//  Block '<S213>/Data Type Duplicate' : Unused code path elimination
//  Block '<S214>/Data Type Duplicate' : Unused code path elimination
//  Block '<S215>/Conversion' : Unused code path elimination
//  Block '<S215>/Data Type Duplicate' : Unused code path elimination
//  Block '<S216>/Data Type Duplicate' : Unused code path elimination
//  Block '<S173>/Data Type Duplicate' : Unused code path elimination
//  Block '<S174>/Data Type Duplicate' : Unused code path elimination
//  Block '<S175>/Data Type Duplicate' : Unused code path elimination
//  Block '<S176>/Data Type Duplicate' : Unused code path elimination
//  Block '<S178>/Data Type Duplicate' : Unused code path elimination
//  Block '<S179>/Data Type Duplicate' : Unused code path elimination
//  Block '<S180>/Data Type Duplicate' : Unused code path elimination
//  Block '<S181>/Conversion' : Unused code path elimination
//  Block '<S181>/Data Type Duplicate' : Unused code path elimination
//  Block '<S182>/Data Type Duplicate' : Unused code path elimination
//  Block '<S183>/Data Type Duplicate' : Unused code path elimination
//  Block '<S184>/Data Type Duplicate' : Unused code path elimination
//  Block '<S186>/Data Type Duplicate' : Unused code path elimination
//  Block '<S187>/Data Type Duplicate' : Unused code path elimination
//  Block '<S4>/G' : Unused code path elimination
//  Block '<S4>/H' : Unused code path elimination
//  Block '<S4>/N' : Unused code path elimination
//  Block '<S4>/P0' : Unused code path elimination
//  Block '<S4>/Q' : Unused code path elimination
//  Block '<S4>/R' : Unused code path elimination
//  Block '<S211>/CheckSignalProperties' : Unused code path elimination
//  Block '<S212>/CheckSignalProperties' : Unused code path elimination
//  Block '<S267>/Data Type Duplicate' : Unused code path elimination
//  Block '<S268>/Data Type Duplicate' : Unused code path elimination
//  Block '<S269>/Conversion' : Unused code path elimination
//  Block '<S269>/Data Type Duplicate' : Unused code path elimination
//  Block '<S270>/Data Type Duplicate' : Unused code path elimination
//  Block '<S227>/Data Type Duplicate' : Unused code path elimination
//  Block '<S228>/Data Type Duplicate' : Unused code path elimination
//  Block '<S229>/Data Type Duplicate' : Unused code path elimination
//  Block '<S230>/Data Type Duplicate' : Unused code path elimination
//  Block '<S232>/Data Type Duplicate' : Unused code path elimination
//  Block '<S233>/Data Type Duplicate' : Unused code path elimination
//  Block '<S234>/Data Type Duplicate' : Unused code path elimination
//  Block '<S235>/Conversion' : Unused code path elimination
//  Block '<S235>/Data Type Duplicate' : Unused code path elimination
//  Block '<S236>/Data Type Duplicate' : Unused code path elimination
//  Block '<S237>/Data Type Duplicate' : Unused code path elimination
//  Block '<S238>/Data Type Duplicate' : Unused code path elimination
//  Block '<S240>/Data Type Duplicate' : Unused code path elimination
//  Block '<S241>/Data Type Duplicate' : Unused code path elimination
//  Block '<S242>/Data Type Duplicate' : Unused code path elimination
//  Block '<S5>/G' : Unused code path elimination
//  Block '<S5>/H' : Unused code path elimination
//  Block '<S5>/N' : Unused code path elimination
//  Block '<S5>/P0' : Unused code path elimination
//  Block '<S5>/Q' : Unused code path elimination
//  Block '<S5>/R' : Unused code path elimination
//  Block '<S266>/CheckSignalProperties' : Unused code path elimination
//  Block '<S321>/Data Type Duplicate' : Unused code path elimination
//  Block '<S322>/Data Type Duplicate' : Unused code path elimination
//  Block '<S323>/Conversion' : Unused code path elimination
//  Block '<S323>/Data Type Duplicate' : Unused code path elimination
//  Block '<S324>/Data Type Duplicate' : Unused code path elimination
//  Block '<S281>/Data Type Duplicate' : Unused code path elimination
//  Block '<S282>/Data Type Duplicate' : Unused code path elimination
//  Block '<S283>/Data Type Duplicate' : Unused code path elimination
//  Block '<S284>/Data Type Duplicate' : Unused code path elimination
//  Block '<S286>/Data Type Duplicate' : Unused code path elimination
//  Block '<S287>/Data Type Duplicate' : Unused code path elimination
//  Block '<S288>/Data Type Duplicate' : Unused code path elimination
//  Block '<S289>/Conversion' : Unused code path elimination
//  Block '<S289>/Data Type Duplicate' : Unused code path elimination
//  Block '<S290>/Data Type Duplicate' : Unused code path elimination
//  Block '<S291>/Data Type Duplicate' : Unused code path elimination
//  Block '<S292>/Data Type Duplicate' : Unused code path elimination
//  Block '<S294>/Data Type Duplicate' : Unused code path elimination
//  Block '<S295>/Data Type Duplicate' : Unused code path elimination
//  Block '<S296>/Data Type Duplicate' : Unused code path elimination
//  Block '<S6>/G' : Unused code path elimination
//  Block '<S6>/H' : Unused code path elimination
//  Block '<S6>/N' : Unused code path elimination
//  Block '<S6>/P0' : Unused code path elimination
//  Block '<S6>/Q' : Unused code path elimination
//  Block '<S6>/R' : Unused code path elimination
//  Block '<S320>/CheckSignalProperties' : Unused code path elimination
//  Block '<Root>/Scope1' : Unused code path elimination
//  Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion2' : Eliminate redundant data type conversion
//  Block '<Root>/Data Type Conversion3' : Eliminate redundant data type conversion
//  Block '<S51>/Conversion' : Eliminate redundant data type conversion
//  Block '<S52>/Conversion' : Eliminate redundant data type conversion
//  Block '<S54>/Conversion' : Eliminate redundant data type conversion
//  Block '<S24>/Conversion' : Eliminate redundant data type conversion
//  Block '<S28>/Reshape' : Reshape block reduction
//  Block '<S1>/ReshapeX0' : Reshape block reduction
//  Block '<S1>/Reshapeu' : Reshape block reduction
//  Block '<S1>/Reshapexhat' : Reshape block reduction
//  Block '<S1>/Reshapey' : Reshape block reduction
//  Block '<S105>/Conversion' : Eliminate redundant data type conversion
//  Block '<S106>/Conversion' : Eliminate redundant data type conversion
//  Block '<S108>/Conversion' : Eliminate redundant data type conversion
//  Block '<S78>/Conversion' : Eliminate redundant data type conversion
//  Block '<S82>/Reshape' : Reshape block reduction
//  Block '<S2>/ReshapeX0' : Reshape block reduction
//  Block '<S2>/Reshapeu' : Reshape block reduction
//  Block '<S2>/Reshapexhat' : Reshape block reduction
//  Block '<S2>/Reshapey' : Reshape block reduction
//  Block '<S159>/Conversion' : Eliminate redundant data type conversion
//  Block '<S160>/Conversion' : Eliminate redundant data type conversion
//  Block '<S162>/Conversion' : Eliminate redundant data type conversion
//  Block '<S132>/Conversion' : Eliminate redundant data type conversion
//  Block '<S136>/Reshape' : Reshape block reduction
//  Block '<S3>/ReshapeX0' : Reshape block reduction
//  Block '<S3>/Reshapeu' : Reshape block reduction
//  Block '<S3>/Reshapexhat' : Reshape block reduction
//  Block '<S3>/Reshapey' : Reshape block reduction
//  Block '<S213>/Conversion' : Eliminate redundant data type conversion
//  Block '<S214>/Conversion' : Eliminate redundant data type conversion
//  Block '<S216>/Conversion' : Eliminate redundant data type conversion
//  Block '<S186>/Conversion' : Eliminate redundant data type conversion
//  Block '<S190>/Reshape' : Reshape block reduction
//  Block '<S4>/ReshapeX0' : Reshape block reduction
//  Block '<S4>/Reshapeu' : Reshape block reduction
//  Block '<S4>/Reshapexhat' : Reshape block reduction
//  Block '<S4>/Reshapey' : Reshape block reduction
//  Block '<S267>/Conversion' : Eliminate redundant data type conversion
//  Block '<S268>/Conversion' : Eliminate redundant data type conversion
//  Block '<S270>/Conversion' : Eliminate redundant data type conversion
//  Block '<S240>/Conversion' : Eliminate redundant data type conversion
//  Block '<S244>/Reshape' : Reshape block reduction
//  Block '<S5>/ReshapeX0' : Reshape block reduction
//  Block '<S5>/Reshapeu' : Reshape block reduction
//  Block '<S5>/Reshapexhat' : Reshape block reduction
//  Block '<S5>/Reshapey' : Reshape block reduction
//  Block '<S321>/Conversion' : Eliminate redundant data type conversion
//  Block '<S322>/Conversion' : Eliminate redundant data type conversion
//  Block '<S324>/Conversion' : Eliminate redundant data type conversion
//  Block '<S294>/Conversion' : Eliminate redundant data type conversion
//  Block '<S298>/Reshape' : Reshape block reduction
//  Block '<S6>/ReshapeX0' : Reshape block reduction
//  Block '<S6>/Reshapeu' : Reshape block reduction
//  Block '<S6>/Reshapexhat' : Reshape block reduction
//  Block '<S6>/Reshapey' : Reshape block reduction


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'INS_Model_C'
//  '<S1>'   : 'INS_Model_C/Kalman Filter'
//  '<S2>'   : 'INS_Model_C/Kalman Filter - X Axis'
//  '<S3>'   : 'INS_Model_C/Kalman Filter - Y Axis'
//  '<S4>'   : 'INS_Model_C/Kalman Filter - Z Axis'
//  '<S5>'   : 'INS_Model_C/Kalman Filter1'
//  '<S6>'   : 'INS_Model_C/Kalman Filter2'
//  '<S7>'   : 'INS_Model_C/Quaternion Rotation'
//  '<S8>'   : 'INS_Model_C/Kalman Filter/CalculatePL'
//  '<S9>'   : 'INS_Model_C/Kalman Filter/CalculateYhat'
//  '<S10>'  : 'INS_Model_C/Kalman Filter/CovarianceOutputConfigurator'
//  '<S11>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionA'
//  '<S12>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionB'
//  '<S13>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionC'
//  '<S14>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionD'
//  '<S15>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionEnable'
//  '<S16>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionG'
//  '<S17>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionH'
//  '<S18>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionN'
//  '<S19>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionP'
//  '<S20>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionP0'
//  '<S21>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionQ'
//  '<S22>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionR'
//  '<S23>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionReset'
//  '<S24>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionX'
//  '<S25>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionX0'
//  '<S26>'  : 'INS_Model_C/Kalman Filter/DataTypeConversionu'
//  '<S27>'  : 'INS_Model_C/Kalman Filter/MemoryP'
//  '<S28>'  : 'INS_Model_C/Kalman Filter/Observer'
//  '<S29>'  : 'INS_Model_C/Kalman Filter/ReducedQRN'
//  '<S30>'  : 'INS_Model_C/Kalman Filter/Reset'
//  '<S31>'  : 'INS_Model_C/Kalman Filter/Reshapeyhat'
//  '<S32>'  : 'INS_Model_C/Kalman Filter/ScalarExpansionP0'
//  '<S33>'  : 'INS_Model_C/Kalman Filter/ScalarExpansionQ'
//  '<S34>'  : 'INS_Model_C/Kalman Filter/ScalarExpansionR'
//  '<S35>'  : 'INS_Model_C/Kalman Filter/UseCurrentEstimator'
//  '<S36>'  : 'INS_Model_C/Kalman Filter/checkA'
//  '<S37>'  : 'INS_Model_C/Kalman Filter/checkB'
//  '<S38>'  : 'INS_Model_C/Kalman Filter/checkC'
//  '<S39>'  : 'INS_Model_C/Kalman Filter/checkD'
//  '<S40>'  : 'INS_Model_C/Kalman Filter/checkEnable'
//  '<S41>'  : 'INS_Model_C/Kalman Filter/checkG'
//  '<S42>'  : 'INS_Model_C/Kalman Filter/checkH'
//  '<S43>'  : 'INS_Model_C/Kalman Filter/checkN'
//  '<S44>'  : 'INS_Model_C/Kalman Filter/checkP0'
//  '<S45>'  : 'INS_Model_C/Kalman Filter/checkQ'
//  '<S46>'  : 'INS_Model_C/Kalman Filter/checkR'
//  '<S47>'  : 'INS_Model_C/Kalman Filter/checkReset'
//  '<S48>'  : 'INS_Model_C/Kalman Filter/checkX0'
//  '<S49>'  : 'INS_Model_C/Kalman Filter/checku'
//  '<S50>'  : 'INS_Model_C/Kalman Filter/checky'
//  '<S51>'  : 'INS_Model_C/Kalman Filter/CalculatePL/DataTypeConversionL'
//  '<S52>'  : 'INS_Model_C/Kalman Filter/CalculatePL/DataTypeConversionM'
//  '<S53>'  : 'INS_Model_C/Kalman Filter/CalculatePL/DataTypeConversionP'
//  '<S54>'  : 'INS_Model_C/Kalman Filter/CalculatePL/DataTypeConversionZ'
//  '<S55>'  : 'INS_Model_C/Kalman Filter/CalculatePL/Ground'
//  '<S56>'  : 'INS_Model_C/Kalman Filter/CalculateYhat/Ground'
//  '<S57>'  : 'INS_Model_C/Kalman Filter/CovarianceOutputConfigurator/decideOutput'
//  '<S58>'  : 'INS_Model_C/Kalman Filter/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
//  '<S59>'  : 'INS_Model_C/Kalman Filter/Observer/MeasurementUpdate'
//  '<S60>'  : 'INS_Model_C/Kalman Filter/ReducedQRN/Ground'
//  '<S61>'  : 'INS_Model_C/Kalman Filter/UseCurrentEstimator/Enabled Subsystem'
//  '<S62>'  : 'INS_Model_C/Kalman Filter - X Axis/CalculatePL'
//  '<S63>'  : 'INS_Model_C/Kalman Filter - X Axis/CalculateYhat'
//  '<S64>'  : 'INS_Model_C/Kalman Filter - X Axis/CovarianceOutputConfigurator'
//  '<S65>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionA'
//  '<S66>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionB'
//  '<S67>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionC'
//  '<S68>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionD'
//  '<S69>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionEnable'
//  '<S70>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionG'
//  '<S71>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionH'
//  '<S72>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionN'
//  '<S73>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionP'
//  '<S74>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionP0'
//  '<S75>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionQ'
//  '<S76>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionR'
//  '<S77>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionReset'
//  '<S78>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionX'
//  '<S79>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionX0'
//  '<S80>'  : 'INS_Model_C/Kalman Filter - X Axis/DataTypeConversionu'
//  '<S81>'  : 'INS_Model_C/Kalman Filter - X Axis/MemoryP'
//  '<S82>'  : 'INS_Model_C/Kalman Filter - X Axis/Observer'
//  '<S83>'  : 'INS_Model_C/Kalman Filter - X Axis/ReducedQRN'
//  '<S84>'  : 'INS_Model_C/Kalman Filter - X Axis/Reset'
//  '<S85>'  : 'INS_Model_C/Kalman Filter - X Axis/Reshapeyhat'
//  '<S86>'  : 'INS_Model_C/Kalman Filter - X Axis/ScalarExpansionP0'
//  '<S87>'  : 'INS_Model_C/Kalman Filter - X Axis/ScalarExpansionQ'
//  '<S88>'  : 'INS_Model_C/Kalman Filter - X Axis/ScalarExpansionR'
//  '<S89>'  : 'INS_Model_C/Kalman Filter - X Axis/UseCurrentEstimator'
//  '<S90>'  : 'INS_Model_C/Kalman Filter - X Axis/checkA'
//  '<S91>'  : 'INS_Model_C/Kalman Filter - X Axis/checkB'
//  '<S92>'  : 'INS_Model_C/Kalman Filter - X Axis/checkC'
//  '<S93>'  : 'INS_Model_C/Kalman Filter - X Axis/checkD'
//  '<S94>'  : 'INS_Model_C/Kalman Filter - X Axis/checkEnable'
//  '<S95>'  : 'INS_Model_C/Kalman Filter - X Axis/checkG'
//  '<S96>'  : 'INS_Model_C/Kalman Filter - X Axis/checkH'
//  '<S97>'  : 'INS_Model_C/Kalman Filter - X Axis/checkN'
//  '<S98>'  : 'INS_Model_C/Kalman Filter - X Axis/checkP0'
//  '<S99>'  : 'INS_Model_C/Kalman Filter - X Axis/checkQ'
//  '<S100>' : 'INS_Model_C/Kalman Filter - X Axis/checkR'
//  '<S101>' : 'INS_Model_C/Kalman Filter - X Axis/checkReset'
//  '<S102>' : 'INS_Model_C/Kalman Filter - X Axis/checkX0'
//  '<S103>' : 'INS_Model_C/Kalman Filter - X Axis/checku'
//  '<S104>' : 'INS_Model_C/Kalman Filter - X Axis/checky'
//  '<S105>' : 'INS_Model_C/Kalman Filter - X Axis/CalculatePL/DataTypeConversionL'
//  '<S106>' : 'INS_Model_C/Kalman Filter - X Axis/CalculatePL/DataTypeConversionM'
//  '<S107>' : 'INS_Model_C/Kalman Filter - X Axis/CalculatePL/DataTypeConversionP'
//  '<S108>' : 'INS_Model_C/Kalman Filter - X Axis/CalculatePL/DataTypeConversionZ'
//  '<S109>' : 'INS_Model_C/Kalman Filter - X Axis/CalculatePL/Ground'
//  '<S110>' : 'INS_Model_C/Kalman Filter - X Axis/CalculateYhat/Ground'
//  '<S111>' : 'INS_Model_C/Kalman Filter - X Axis/CovarianceOutputConfigurator/decideOutput'
//  '<S112>' : 'INS_Model_C/Kalman Filter - X Axis/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
//  '<S113>' : 'INS_Model_C/Kalman Filter - X Axis/Observer/MeasurementUpdate'
//  '<S114>' : 'INS_Model_C/Kalman Filter - X Axis/ReducedQRN/Ground'
//  '<S115>' : 'INS_Model_C/Kalman Filter - X Axis/UseCurrentEstimator/Enabled Subsystem'
//  '<S116>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculatePL'
//  '<S117>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculateYhat'
//  '<S118>' : 'INS_Model_C/Kalman Filter - Y Axis/CovarianceOutputConfigurator'
//  '<S119>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionA'
//  '<S120>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionB'
//  '<S121>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionC'
//  '<S122>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionD'
//  '<S123>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionEnable'
//  '<S124>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionG'
//  '<S125>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionH'
//  '<S126>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionN'
//  '<S127>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionP'
//  '<S128>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionP0'
//  '<S129>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionQ'
//  '<S130>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionR'
//  '<S131>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionReset'
//  '<S132>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionX'
//  '<S133>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionX0'
//  '<S134>' : 'INS_Model_C/Kalman Filter - Y Axis/DataTypeConversionu'
//  '<S135>' : 'INS_Model_C/Kalman Filter - Y Axis/MemoryP'
//  '<S136>' : 'INS_Model_C/Kalman Filter - Y Axis/Observer'
//  '<S137>' : 'INS_Model_C/Kalman Filter - Y Axis/ReducedQRN'
//  '<S138>' : 'INS_Model_C/Kalman Filter - Y Axis/Reset'
//  '<S139>' : 'INS_Model_C/Kalman Filter - Y Axis/Reshapeyhat'
//  '<S140>' : 'INS_Model_C/Kalman Filter - Y Axis/ScalarExpansionP0'
//  '<S141>' : 'INS_Model_C/Kalman Filter - Y Axis/ScalarExpansionQ'
//  '<S142>' : 'INS_Model_C/Kalman Filter - Y Axis/ScalarExpansionR'
//  '<S143>' : 'INS_Model_C/Kalman Filter - Y Axis/UseCurrentEstimator'
//  '<S144>' : 'INS_Model_C/Kalman Filter - Y Axis/checkA'
//  '<S145>' : 'INS_Model_C/Kalman Filter - Y Axis/checkB'
//  '<S146>' : 'INS_Model_C/Kalman Filter - Y Axis/checkC'
//  '<S147>' : 'INS_Model_C/Kalman Filter - Y Axis/checkD'
//  '<S148>' : 'INS_Model_C/Kalman Filter - Y Axis/checkEnable'
//  '<S149>' : 'INS_Model_C/Kalman Filter - Y Axis/checkG'
//  '<S150>' : 'INS_Model_C/Kalman Filter - Y Axis/checkH'
//  '<S151>' : 'INS_Model_C/Kalman Filter - Y Axis/checkN'
//  '<S152>' : 'INS_Model_C/Kalman Filter - Y Axis/checkP0'
//  '<S153>' : 'INS_Model_C/Kalman Filter - Y Axis/checkQ'
//  '<S154>' : 'INS_Model_C/Kalman Filter - Y Axis/checkR'
//  '<S155>' : 'INS_Model_C/Kalman Filter - Y Axis/checkReset'
//  '<S156>' : 'INS_Model_C/Kalman Filter - Y Axis/checkX0'
//  '<S157>' : 'INS_Model_C/Kalman Filter - Y Axis/checku'
//  '<S158>' : 'INS_Model_C/Kalman Filter - Y Axis/checky'
//  '<S159>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculatePL/DataTypeConversionL'
//  '<S160>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculatePL/DataTypeConversionM'
//  '<S161>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculatePL/DataTypeConversionP'
//  '<S162>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculatePL/DataTypeConversionZ'
//  '<S163>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculatePL/Ground'
//  '<S164>' : 'INS_Model_C/Kalman Filter - Y Axis/CalculateYhat/Ground'
//  '<S165>' : 'INS_Model_C/Kalman Filter - Y Axis/CovarianceOutputConfigurator/decideOutput'
//  '<S166>' : 'INS_Model_C/Kalman Filter - Y Axis/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
//  '<S167>' : 'INS_Model_C/Kalman Filter - Y Axis/Observer/MeasurementUpdate'
//  '<S168>' : 'INS_Model_C/Kalman Filter - Y Axis/ReducedQRN/Ground'
//  '<S169>' : 'INS_Model_C/Kalman Filter - Y Axis/UseCurrentEstimator/Enabled Subsystem'
//  '<S170>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculatePL'
//  '<S171>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculateYhat'
//  '<S172>' : 'INS_Model_C/Kalman Filter - Z Axis/CovarianceOutputConfigurator'
//  '<S173>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionA'
//  '<S174>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionB'
//  '<S175>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionC'
//  '<S176>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionD'
//  '<S177>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionEnable'
//  '<S178>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionG'
//  '<S179>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionH'
//  '<S180>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionN'
//  '<S181>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionP'
//  '<S182>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionP0'
//  '<S183>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionQ'
//  '<S184>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionR'
//  '<S185>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionReset'
//  '<S186>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionX'
//  '<S187>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionX0'
//  '<S188>' : 'INS_Model_C/Kalman Filter - Z Axis/DataTypeConversionu'
//  '<S189>' : 'INS_Model_C/Kalman Filter - Z Axis/MemoryP'
//  '<S190>' : 'INS_Model_C/Kalman Filter - Z Axis/Observer'
//  '<S191>' : 'INS_Model_C/Kalman Filter - Z Axis/ReducedQRN'
//  '<S192>' : 'INS_Model_C/Kalman Filter - Z Axis/Reset'
//  '<S193>' : 'INS_Model_C/Kalman Filter - Z Axis/Reshapeyhat'
//  '<S194>' : 'INS_Model_C/Kalman Filter - Z Axis/ScalarExpansionP0'
//  '<S195>' : 'INS_Model_C/Kalman Filter - Z Axis/ScalarExpansionQ'
//  '<S196>' : 'INS_Model_C/Kalman Filter - Z Axis/ScalarExpansionR'
//  '<S197>' : 'INS_Model_C/Kalman Filter - Z Axis/UseCurrentEstimator'
//  '<S198>' : 'INS_Model_C/Kalman Filter - Z Axis/checkA'
//  '<S199>' : 'INS_Model_C/Kalman Filter - Z Axis/checkB'
//  '<S200>' : 'INS_Model_C/Kalman Filter - Z Axis/checkC'
//  '<S201>' : 'INS_Model_C/Kalman Filter - Z Axis/checkD'
//  '<S202>' : 'INS_Model_C/Kalman Filter - Z Axis/checkEnable'
//  '<S203>' : 'INS_Model_C/Kalman Filter - Z Axis/checkG'
//  '<S204>' : 'INS_Model_C/Kalman Filter - Z Axis/checkH'
//  '<S205>' : 'INS_Model_C/Kalman Filter - Z Axis/checkN'
//  '<S206>' : 'INS_Model_C/Kalman Filter - Z Axis/checkP0'
//  '<S207>' : 'INS_Model_C/Kalman Filter - Z Axis/checkQ'
//  '<S208>' : 'INS_Model_C/Kalman Filter - Z Axis/checkR'
//  '<S209>' : 'INS_Model_C/Kalman Filter - Z Axis/checkReset'
//  '<S210>' : 'INS_Model_C/Kalman Filter - Z Axis/checkX0'
//  '<S211>' : 'INS_Model_C/Kalman Filter - Z Axis/checku'
//  '<S212>' : 'INS_Model_C/Kalman Filter - Z Axis/checky'
//  '<S213>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculatePL/DataTypeConversionL'
//  '<S214>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculatePL/DataTypeConversionM'
//  '<S215>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculatePL/DataTypeConversionP'
//  '<S216>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculatePL/DataTypeConversionZ'
//  '<S217>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculatePL/Ground'
//  '<S218>' : 'INS_Model_C/Kalman Filter - Z Axis/CalculateYhat/Ground'
//  '<S219>' : 'INS_Model_C/Kalman Filter - Z Axis/CovarianceOutputConfigurator/decideOutput'
//  '<S220>' : 'INS_Model_C/Kalman Filter - Z Axis/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
//  '<S221>' : 'INS_Model_C/Kalman Filter - Z Axis/Observer/MeasurementUpdate'
//  '<S222>' : 'INS_Model_C/Kalman Filter - Z Axis/ReducedQRN/Ground'
//  '<S223>' : 'INS_Model_C/Kalman Filter - Z Axis/UseCurrentEstimator/Enabled Subsystem'
//  '<S224>' : 'INS_Model_C/Kalman Filter1/CalculatePL'
//  '<S225>' : 'INS_Model_C/Kalman Filter1/CalculateYhat'
//  '<S226>' : 'INS_Model_C/Kalman Filter1/CovarianceOutputConfigurator'
//  '<S227>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionA'
//  '<S228>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionB'
//  '<S229>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionC'
//  '<S230>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionD'
//  '<S231>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionEnable'
//  '<S232>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionG'
//  '<S233>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionH'
//  '<S234>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionN'
//  '<S235>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionP'
//  '<S236>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionP0'
//  '<S237>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionQ'
//  '<S238>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionR'
//  '<S239>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionReset'
//  '<S240>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionX'
//  '<S241>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionX0'
//  '<S242>' : 'INS_Model_C/Kalman Filter1/DataTypeConversionu'
//  '<S243>' : 'INS_Model_C/Kalman Filter1/MemoryP'
//  '<S244>' : 'INS_Model_C/Kalman Filter1/Observer'
//  '<S245>' : 'INS_Model_C/Kalman Filter1/ReducedQRN'
//  '<S246>' : 'INS_Model_C/Kalman Filter1/Reset'
//  '<S247>' : 'INS_Model_C/Kalman Filter1/Reshapeyhat'
//  '<S248>' : 'INS_Model_C/Kalman Filter1/ScalarExpansionP0'
//  '<S249>' : 'INS_Model_C/Kalman Filter1/ScalarExpansionQ'
//  '<S250>' : 'INS_Model_C/Kalman Filter1/ScalarExpansionR'
//  '<S251>' : 'INS_Model_C/Kalman Filter1/UseCurrentEstimator'
//  '<S252>' : 'INS_Model_C/Kalman Filter1/checkA'
//  '<S253>' : 'INS_Model_C/Kalman Filter1/checkB'
//  '<S254>' : 'INS_Model_C/Kalman Filter1/checkC'
//  '<S255>' : 'INS_Model_C/Kalman Filter1/checkD'
//  '<S256>' : 'INS_Model_C/Kalman Filter1/checkEnable'
//  '<S257>' : 'INS_Model_C/Kalman Filter1/checkG'
//  '<S258>' : 'INS_Model_C/Kalman Filter1/checkH'
//  '<S259>' : 'INS_Model_C/Kalman Filter1/checkN'
//  '<S260>' : 'INS_Model_C/Kalman Filter1/checkP0'
//  '<S261>' : 'INS_Model_C/Kalman Filter1/checkQ'
//  '<S262>' : 'INS_Model_C/Kalman Filter1/checkR'
//  '<S263>' : 'INS_Model_C/Kalman Filter1/checkReset'
//  '<S264>' : 'INS_Model_C/Kalman Filter1/checkX0'
//  '<S265>' : 'INS_Model_C/Kalman Filter1/checku'
//  '<S266>' : 'INS_Model_C/Kalman Filter1/checky'
//  '<S267>' : 'INS_Model_C/Kalman Filter1/CalculatePL/DataTypeConversionL'
//  '<S268>' : 'INS_Model_C/Kalman Filter1/CalculatePL/DataTypeConversionM'
//  '<S269>' : 'INS_Model_C/Kalman Filter1/CalculatePL/DataTypeConversionP'
//  '<S270>' : 'INS_Model_C/Kalman Filter1/CalculatePL/DataTypeConversionZ'
//  '<S271>' : 'INS_Model_C/Kalman Filter1/CalculatePL/Ground'
//  '<S272>' : 'INS_Model_C/Kalman Filter1/CalculateYhat/Ground'
//  '<S273>' : 'INS_Model_C/Kalman Filter1/CovarianceOutputConfigurator/decideOutput'
//  '<S274>' : 'INS_Model_C/Kalman Filter1/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
//  '<S275>' : 'INS_Model_C/Kalman Filter1/Observer/MeasurementUpdate'
//  '<S276>' : 'INS_Model_C/Kalman Filter1/ReducedQRN/Ground'
//  '<S277>' : 'INS_Model_C/Kalman Filter1/UseCurrentEstimator/Enabled Subsystem'
//  '<S278>' : 'INS_Model_C/Kalman Filter2/CalculatePL'
//  '<S279>' : 'INS_Model_C/Kalman Filter2/CalculateYhat'
//  '<S280>' : 'INS_Model_C/Kalman Filter2/CovarianceOutputConfigurator'
//  '<S281>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionA'
//  '<S282>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionB'
//  '<S283>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionC'
//  '<S284>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionD'
//  '<S285>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionEnable'
//  '<S286>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionG'
//  '<S287>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionH'
//  '<S288>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionN'
//  '<S289>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionP'
//  '<S290>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionP0'
//  '<S291>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionQ'
//  '<S292>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionR'
//  '<S293>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionReset'
//  '<S294>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionX'
//  '<S295>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionX0'
//  '<S296>' : 'INS_Model_C/Kalman Filter2/DataTypeConversionu'
//  '<S297>' : 'INS_Model_C/Kalman Filter2/MemoryP'
//  '<S298>' : 'INS_Model_C/Kalman Filter2/Observer'
//  '<S299>' : 'INS_Model_C/Kalman Filter2/ReducedQRN'
//  '<S300>' : 'INS_Model_C/Kalman Filter2/Reset'
//  '<S301>' : 'INS_Model_C/Kalman Filter2/Reshapeyhat'
//  '<S302>' : 'INS_Model_C/Kalman Filter2/ScalarExpansionP0'
//  '<S303>' : 'INS_Model_C/Kalman Filter2/ScalarExpansionQ'
//  '<S304>' : 'INS_Model_C/Kalman Filter2/ScalarExpansionR'
//  '<S305>' : 'INS_Model_C/Kalman Filter2/UseCurrentEstimator'
//  '<S306>' : 'INS_Model_C/Kalman Filter2/checkA'
//  '<S307>' : 'INS_Model_C/Kalman Filter2/checkB'
//  '<S308>' : 'INS_Model_C/Kalman Filter2/checkC'
//  '<S309>' : 'INS_Model_C/Kalman Filter2/checkD'
//  '<S310>' : 'INS_Model_C/Kalman Filter2/checkEnable'
//  '<S311>' : 'INS_Model_C/Kalman Filter2/checkG'
//  '<S312>' : 'INS_Model_C/Kalman Filter2/checkH'
//  '<S313>' : 'INS_Model_C/Kalman Filter2/checkN'
//  '<S314>' : 'INS_Model_C/Kalman Filter2/checkP0'
//  '<S315>' : 'INS_Model_C/Kalman Filter2/checkQ'
//  '<S316>' : 'INS_Model_C/Kalman Filter2/checkR'
//  '<S317>' : 'INS_Model_C/Kalman Filter2/checkReset'
//  '<S318>' : 'INS_Model_C/Kalman Filter2/checkX0'
//  '<S319>' : 'INS_Model_C/Kalman Filter2/checku'
//  '<S320>' : 'INS_Model_C/Kalman Filter2/checky'
//  '<S321>' : 'INS_Model_C/Kalman Filter2/CalculatePL/DataTypeConversionL'
//  '<S322>' : 'INS_Model_C/Kalman Filter2/CalculatePL/DataTypeConversionM'
//  '<S323>' : 'INS_Model_C/Kalman Filter2/CalculatePL/DataTypeConversionP'
//  '<S324>' : 'INS_Model_C/Kalman Filter2/CalculatePL/DataTypeConversionZ'
//  '<S325>' : 'INS_Model_C/Kalman Filter2/CalculatePL/Ground'
//  '<S326>' : 'INS_Model_C/Kalman Filter2/CalculateYhat/Ground'
//  '<S327>' : 'INS_Model_C/Kalman Filter2/CovarianceOutputConfigurator/decideOutput'
//  '<S328>' : 'INS_Model_C/Kalman Filter2/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
//  '<S329>' : 'INS_Model_C/Kalman Filter2/Observer/MeasurementUpdate'
//  '<S330>' : 'INS_Model_C/Kalman Filter2/ReducedQRN/Ground'
//  '<S331>' : 'INS_Model_C/Kalman Filter2/UseCurrentEstimator/Enabled Subsystem'
//  '<S332>' : 'INS_Model_C/Quaternion Rotation/Quaternion Normalize'
//  '<S333>' : 'INS_Model_C/Quaternion Rotation/V1'
//  '<S334>' : 'INS_Model_C/Quaternion Rotation/V2'
//  '<S335>' : 'INS_Model_C/Quaternion Rotation/V3'
//  '<S336>' : 'INS_Model_C/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus'
//  '<S337>' : 'INS_Model_C/Quaternion Rotation/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'

#endif                                 // INS_Model_C_h_

//
// File trailer for generated code.
//
// [EOF]
//
