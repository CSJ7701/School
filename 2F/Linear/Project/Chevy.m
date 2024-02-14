classdef Chevy < LH & BN & Digital
    % Chebyshev Filter Class
    properties
        BPoles
        a
        b
    end

    methods
        function obj = Chevy(Amax,Amin,wp1,wp2,ws1,ws2,ftype,ischild,isdig)
            obj.ischild=ischild; % Sets an object property so that I can identify a prototype filter programatically.
            obj.dig=isdig; % Sets an object property to identify digital filters.
            % Specify filter type
            if ischar(ftype)
                obj.ftype=ftype;
                obj.typenum=obj.Ftype();
            elseif isnumeric(ftype)
                obj.typenum=ftype;
            end
            
            % Set Givens
            obj.Amax=Amax;
            obj.Amin=Amin;
            
            % Change based on typenum
            if ismember(obj.typenum,[1,2])
                obj.ws=ws2;
                obj.wp=wp2;

                % Calculate Values
                obj.rat=obj.Ratio();
                obj.n=obj.Order();
                obj.w0=obj.Calc_w0();
                obj.BPoles=obj.ButterPoles();
                [obj.a,obj.b,obj.poles]=obj.Poles();
                if (obj.typenum==2) % take reciprocal for chebyshev highpass
                    obj.poles=1./obj.poles;
                end
            elseif ismember(obj.typenum,[3,4])
                obj.ws1=ws1;
                obj.ws2=ws2;
                obj.wp1=wp1;
                obj.wp2=wp2;
                [obj.ws1, obj.ws2, obj.wp1, obj.wp2, obj.CF] = obj.EnforceSymmetry();
                obj.ws=obj.ws2-obj.ws1; obj.wp=obj.wp2-obj.wp1; % Enforce Symmetry, then calculate delta ws and wp for prototype filter
                % Calculate values for prototype
                obj.protoFilter=Chevy(obj.Amax,obj.Amin,0,obj.wp,0,obj.ws,obj.typenum-2,1,0);
                if (obj.typenum == 3)
                    % calculate low pass poles for bandpass
                    obj.protoFilter.poles=obj.Poles_static(obj.protoFilter.BPoles,obj.protoFilter.Amax,obj.protoFilter.n);
                elseif (obj.typenum == 4)
                    % calculate reciprocal of highpass poles for notchpass
                    obj.protoFilter.poles=1./obj.Poles_static(obj.protoFilter.BPoles,obj.protoFilter.Amax,obj.protoFilter.n);
                end

                obj.rat=obj.protoFilter.rat;
                obj.n=2*obj.protoFilter.n;

                % Convert prototype poles to BP or NP poles
                obj.poles=obj.LH_to_BN();
                obj.wp=1; % normalize wp to 1 - this is for the w0 calculations.

            end
            [w0init,obj.Q]=obj.QW();
            if ((obj.typenum==1)&&(~obj.ischild==1)) % Checks whether lowpass and NOT a prototype filter
                obj.w0=w0init.*obj.wp;
            elseif ((obj.typenum==2)&&(~obj.ischild==1)) % Checks whether lowpass and NOT a prototype filter
                obj.w0=obj.wp.*w0init; % I multiply here because I already took inverse of poles in line 37
            else
                obj.w0=w0init;
            end
            if (~obj.ischild==1)
                obj.Display();
            end
        end

        function n = Order(obj)
            % Calculates Chevy order
            % takes Amin, Amax, Rat
            frac=acosh(sqrt((10^(obj.Amin/10)-1)/(10^(obj.Amax/10)-1))) / acosh(obj.rat);
            n=ceil(frac);
            return
        end

        function poles=ButterPoles(obj)
            % Calculates Butter Order. This is a reimplementation from
            % Butter class
            % Takes n, w0
            k=0:(2*obj.n-1);
           
            if(mod(obj.n,2)==1)
                poles=obj.w0*exp(1i*2*k*pi/(2*obj.n));
            else
                poles=obj.w0*exp(1i*(2*k+1)*pi/(2*obj.n));
            end
            poles=poles(real(poles)<0);
            
            return
        end

        function [a,b,poles]=Poles(obj)
            % Calculates Chevy poles
            % Takes BPoles, Amax, n, typenum, Wp2, Wp1, CF
            angles=(pi-angle(obj.BPoles))*(180/pi);
            E=sqrt(10^(obj.Amax/10)-1);
            a=(1/2)*(((1/E+sqrt((1/E^2)+1))^(1/obj.n))-((1/E+sqrt((1/E^2)+1))^(-1/obj.n)));
            if (obj.typenum<3)
                b=(1/2)*((1/E+sqrt((1/E^2)+1))^(1/obj.n)+(1/E+sqrt((1/E^2)+1))^(-1/obj.n));
            elseif (obj.typenum>2)
                b=(obj.Wp2-obj.Wp1)/obj.CF;
            end
            poles=-a*(cosd(angles))+1i*b*(sind(angles));
            return
        end
    end

    methods (Static)
        function poles=Poles_static(Bpoles,Amax,n)
            % Calculates Chevy order for prototype filter.
            % Takes Bpoles, Amax, n
            angles=(pi-angle(Bpoles))*(180/pi);
            E=sqrt(10^(Amax/10)-1);
            a=(1/2)*(((1/E+sqrt((1/E^2)+1))^(1/n))-((1/E+sqrt((1/E^2)+1))^(-1/n)));
            b=(1/2)*((1/E+sqrt((1/E^2)+1))^(1/n)+(1/E+sqrt((1/E^2)+1))^(-1/n));
            poles=-a*(cosd(angles))+1i*b*(sind(angles));
            return
        end
    end
end
