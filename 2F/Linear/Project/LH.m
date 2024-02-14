classdef LH < Filter
    % Lowpass Highpass Filter Class
    % Defines all functions/variables used in Lowpass and Highpass Filters
    properties  
        % Given
        ws
        wp
    end

    methods
        function rat = Ratio(obj)
            % Calculates ratio based on wp and ws.
            % This is only run for LP and HP filters, in BP and NP filters,
            % this is run for the prototype and inherited by the parent
            % filter.
            if(obj.typenum==1)
                rat=obj.ws/obj.wp;
            elseif(obj.typenum==2)
                rat=obj.wp/obj.ws;
            end
            return
        end
 
        function [w0,Q]=QW(obj)
            % Calculates the w0's and Q's for a filter
            % Outputs 2 results, set equal to an array.
            % DEVNOTE - This should really go into the "Filter" class.
            index=imag(obj.poles)>-1e-12; % Take poles with positive, nonzero imaginary components.
            ppoles=obj.poles(index);
            w0=abs(ppoles);
            Q=(1./(2*cos(pi-angle(ppoles))));
        end

        function w0 = Calc_w0(obj)
            % Calculate w0
            % This is used as an input to the initial Butterpoles function
            if(obj.typenum==1)
                w0=obj.wp/(10^(obj.Amax/10)-1)^(1/2/obj.n);
            elseif (obj.typenum==2)
                w0=obj.wp*(10^(obj.Amax/10)-1)^(1/2/obj.n);
            end
            return
        end

        function Display(obj)
            % Display Routine
            secnum=obj.n/2;
            secnum=ceil(secnum);
            % Determines the number of sections necessary.

            index=(imag(obj.poles)>0)|(imag(obj.poles)==0);
            upoles=obj.poles(index);
            row1=upoles(1:secnum);
            row2=obj.Q(1:secnum);
            row3=obj.w0(1:secnum);
            matrix=[row1;row2;row3];
            matrix=matrix';
            matrix=sortrows(matrix,2);
            % Constructs a matrix sorted by Q where column 1 is poles,
            % column 2 is Q and column 3 is w0.
            
            for i=1:secnum
                fprintf('Section %0.0f:\n   [W0] = %4.4f\n   [Q] = %4.4f\n   [Pole] = %4.2f + %4.2fi\n',i,matrix(i,3),matrix(i,2),real(matrix(i,1)),imag(matrix(i,1)))
            end        
            % 'FOR' loop to print section #, w0, Q, and Poles for each
            % filter section.
        end
    end

    methods (Static) % Static reimplementations for functions above. Redefined for use in prototype filters.
        
        function w0 = Calc_w0_static(Amax,n,wp,typenum)
            if(typenum==1)
                w0=wp/(10^(Amax/10)-1)^(1/2/n);
            elseif (typenum==2)
                w0=wp*(10^(Amax/10)-1)^(1/2/n);
            end
            return
        end

    end

    methods (Abstract)
        % Defines methods that ALL children must have.
        Order(obj)
        Poles(obj)
    end
end