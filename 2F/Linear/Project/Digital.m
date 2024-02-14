 classdef Digital
    % Digital Filter Class
    % Defines all functions/variables used in Digital Filters

    properties
        Coeff % Unused, left here for posterity.
        dig
    end

    methods
        function DigDisplay(obj)
            % Digital Filter display routine.
            % Largely copied from LH/Display function.
            secnum=obj.n/2;
            secnum=ceil(secnum);
            % Calculates necessary number of filter sections.

            index=(imag(obj.poles)>0)|(imag(obj.poles)==0);
            upoles=obj.poles(index);
            row1=upoles(1:secnum);
            row2=obj.Q(1:secnum);
            row3=obj.w0(1:secnum);
            matrix=[row1;row2;row3];
            matrix=matrix.';
            matrix=sortrows(matrix,2);
            % Constructs matrix of poles,Q,and w0. Q is used to sort, w0 is
            % unused here.
            
            for i=1:secnum % this will run for each section, printing line by line
                fprintf('Section %0.0f:\n',i);
                if (abs(imag(matrix(i,1)))<1e-10) % If section is 1st order
                    if (obj.typenum==1)
                        num=[1 1];
                    elseif (obj.typenum==2)
                        num=[1 -1];
                    end
                    den=[1,-real(matrix(i,1))];
                    % TFUNC variables are unused
                    % Originally intended to print a formatted transfer
                    % function with PlotFunc
                    TFuncNum=sprintf('1%+0.1fz⁻¹',num(2));
                    TFuncDen=sprintf('1%+0.4fz⁻¹',den(2));
                    %PlotFunc=sprintf('(1%+0.0fz^-1)/(1%+0.4fz^-1)',num(2),den(2));
                else % If section is 2nd order
                    if (obj.typenum==1)
                        num=[1 2 1];
                    elseif (obj.typenum==2)
                        num=[1 -2 1];
                    elseif (obj.typenum==3)
                        num=[1 0 -1];
                    elseif (obj.typenum==4)
                        num=[1 -2*cos(2*pi*Digital.Unwarp(obj.CF)) 1];
                    end
                    den=[1, -2*real(matrix(i,1)), abs(matrix(i,1))^2];

                    % Again, unused but retained for posterity.
                    TFuncNum=sprintf('1%+0.1fz⁻¹%+0.1fz⁻²',num(2),num(3));
                    TFuncDen=sprintf('1%+0.4fz⁻¹%+0.4fz⁻²',den(2),den(3));                    
                    %PlotFunc=sprintf('(1%+0.0fz^(-1)%+0.0fz^(-2))/(1%+0.4fz^(-1)%+0.4fz^(-2))',num(2),num(3),den(2),den(3));
                end

                fprintf('   Num:  ');
                fprintf('%0.4f  ',num);
                fprintf('\n');
                fprintf('   Den:  ')
                fprintf('%0.4f  ',den);
                fprintf('\n');
                %fprintf('\n   Transfer Function: %s\n                      %s\n',TFuncNum,TFuncDen);
            end
        end
    end

    

    methods (Static)

        function newfreq=Prewarp(oldfreq)
            % Prewarps for Digital Filter Frequencies
            % Equation 10.12
            newfreq=2*tan(2*pi*oldfreq/2);
            return
        end

        function newfreq=Unwarp(oldfreq)
            % Returns: frequency in fractions of Fs (0.2 for 0.2 Fs)
            % Equation 10.11 (Inverse of Prewarp)
            newfreq=2*(atan(oldfreq/2))/(2*pi);
            return
        end

        function zpoles=Bilin(spoles)
            % Equation 10.8
            % Bilinear transformation to map poles in s plane to z plane.
            zpoles=(2+spoles)./(2-spoles);
            return
        end
    end
 end
