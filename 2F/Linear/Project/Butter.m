classdef Butter < LH & BN & Digital
    % Butterworth Filter Class
    properties
    end

    methods
        function obj = Butter(Amax,Amin,wp1,wp2,ws1,ws2,ftype,ischild,isdig)
            obj.ischild=ischild; % Sets an object property so that I can identify a prototype filter programatically.
            obj.dig=isdig; % Sets an object property to identify digital filters.
            if ischar(ftype) % This 'if' block checks whether ftype is passed as an integer or a character. 
                obj.ftype=ftype; % This is to ensure compatability with bandpass and notch prototype filters.
                obj.typenum=obj.Ftype();
            elseif isnumeric(ftype)
                obj.typenum=ftype;
            end
            
            % Set givens
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
                obj.poles=obj.Poles();

            elseif ismember(obj.typenum,[3,4])
                % Set givens
                obj.ws1=ws1;
                obj.ws2=ws2;
                obj.wp1=wp1;
                obj.wp2=wp2;
                [obj.ws1,obj.ws2,obj.wp1,obj.wp2,obj.CF] = obj.EnforceSymmetry();
                obj.ws=obj.ws2-obj.ws1; obj.wp=obj.wp2-obj.wp1;
                % Calculate Values for prototype
                obj.protoFilter=Butter(obj.Amax,obj.Amin,0,obj.wp,0,obj.ws,obj.typenum-2,1,0);
                obj.protoFilter.w0=obj.Calc_w0_static(obj.Amax,obj.protoFilter.n,1,obj.typenum-2);
                obj.protoFilter.poles=obj.Poles_static(obj.protoFilter.n,obj.protoFilter.w0);

                obj.rat=obj.protoFilter.rat;
                obj.n=2*obj.protoFilter.n;

                % Convert prototype poles to BP or NP poles
                obj.poles=obj.LH_to_BN();            
            end
    
            [obj.w0,obj.Q]=obj.QW();

            % Only run the display routine if it is NOT a child filter
            if (~obj.ischild==1)
                %obj.Display();
            end
        end

        function n = Order(obj)
            % Calculates Butterworth order
            % Takes Amin, Amax, Rat
            frac=log((10^(obj.Amin/10)-1)/(10^(obj.Amax/10)-1))/(2*log(obj.rat));
            n=ceil(abs(frac));
            obj.n=n;
            return
        end

        function poles=Poles(obj)
            % Calculates Butterworth Poles
            % Takes n, w0 (Calculated using Calc_w0)
            k=0:(2*obj.n-1);
            if(mod(obj.n,2)==1)
                poles=obj.w0*exp(1i*2*k*pi/(2*obj.n));
            else
                poles=obj.w0*exp(1i*(2*k+1)*pi/(2*obj.n));
            end
            poles=poles(real(poles)<0);
            return
        end


    end

    methods (Static)

        function poles=Poles_static(n,w0)
            % Static reimplimentation of Butterworth Poles for prototype
            % filters
            % Takes n, w0
            k=0:(2*n-1);
            if(mod(n,2)==1)
                poles=w0*exp(1i*2*k*pi/(2*n));
            else
                poles=w0*exp(1i*(2*k+1)*pi/(2*n));
            end
            poles=poles(real(poles)<0);
            return
        end


    end
end