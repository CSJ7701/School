%% SETUP_SRV02_lab2_MDL
%
% Sets the necessary parameters to run the SRV02 Experiment #1: Modeling
% laboratory using the "q_srv02_mdl" Simulink diagram.
% 
% Copyright (C) 2010 Quanser Consulting Inc.
%
clear all;
%
%% SRV02 Configuration
% External Gear Configuration: set to 'HIGH' or 'LOW'
EXT_GEAR_CONFIG = 'HIGH';
% Encoder Type: set to 'E' or 'EHR'
ENCODER_TYPE = 'E';
% Is SRV02 equipped with Tachometer? (i.e. option T): set to 'YES' or 'NO'
TACH_OPTION = 'YES';
% Type of Load: set to 'NONE', 'DISC', or 'BAR'
LOAD_TYPE = 'DISC';
% Amplifier Gain: set VoltPAQ amplifier gain to 1
K_AMP = 1;
% Power Amplifier Type: set to 'VoltPAQ', 'UPM_1503', 'UPM_2405', or 'Q3'
AMP_TYPE = 'VoltPAQ';
% Digital-to-Analog Maximum Voltage (V)
VMAX_DAC = 10;
%
%% Lab Configuration
% Type of Controller: set it to 'AUTO', 'MANUAL'
%MODELING_TYPE = 'AUTO';   
 MODELING_TYPE = 'MANUAL';
%
%% SRV02 System Parameters
% Set Model Variables Accordingly to the USER-DEFINED SRV02 System Configuration
% Also Calculate the SRV02 Model Parameters and 
% Write them to the MATLAB Workspace (to be used in Simulink diagrams)
[ Rm, kt, km, Kg, eta_g, Beq, Jm, Jeq, eta_m, K_POT, K_TACH, K_ENC, VMAX_AMP, IMAX_AMP ] = config_srv02( EXT_GEAR_CONFIG, ENCODER_TYPE, TACH_OPTION, AMP_TYPE, LOAD_TYPE );
%
%% Filter Parameters
% Encoder high-pass filter used to compute velocity
% Cutoff frequency (rad/s)
wcf_e = 2 * pi * 25.0;
% Damping ratio
zetaf_e = 0.9;
%
%% SRV02 Model Parameters
if strcmp ( MODELING_TYPE , 'MANUAL' )
     %Default model parameters
    if strcmp(AMP_TYPE,'Q3')
        K = 50;
        tau = 1;
    else
        K =1;
        tau = 0.1;
    end
else    
    [K,tau] = d_model_param(Rm, kt, km, Kg, eta_g, Beq, Jeq, eta_m, AMP_TYPE);
end
%
%% Display
disp( 'Calculated SRV02 model parameter: ' )
if strcmp(AMP_TYPE,'Q3')
    disp( [ '   K = ' num2str( K, 4 ) ' rad/s^2/A' ] )
else
    disp( [ '   K = ' num2str( K, 3 ) ' rad/s/V' ] )
    disp( [ '   tau = ' num2str( tau, 3 ) ' s' ] )
end
