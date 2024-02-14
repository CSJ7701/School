classdef BN < Filter
    % Bandpass and Notch Filter Class
    % Defines all functions/variables used in Bandpass or Notch filters

    properties
        % Given
        ws1
        ws2
        wp1
        wp2

        % Calculated
        CF

        % Background
        ischild
        protoFilter
    end

    methods
        function [ws1sym, ws2sym, wp1sym, wp2sym, CF] = EnforceSymmetry(obj)
            % Enforces symmetry in Bandpass and Notch Filters
            % Takes wp1,wp2,ws2,ws2 from object

            % BP
            if (obj.typenum == 3)
                if obj.ws1 > obj.wp1*obj.wp2/obj.ws2
                    ws2sym = obj.wp1*obj.wp2/obj.ws1;
                    ws1sym = obj.ws1;
                else
                    ws1sym = obj.wp1*obj.wp2/obj.ws2;
                    ws2sym = obj.ws2;
                end
                wp1sym=obj.wp1;
                wp2sym=obj.wp2;
                
            % NP
            elseif (obj.typenum==4)
                if obj.wp1 < obj.ws1*obj.ws2/obj.wp2
                    wp1sym = obj.ws1*obj.ws2/obj.wp2;
                    wp2sym = obj.wp2;
                else
                    wp2sym = obj.ws1*obj.ws2/obj.wp1;
                    wp1sym = obj.wp1;
                end
                ws1sym = obj.ws1;
                ws2sym = obj.ws2;
            end
            CF = sqrt(wp2sym*wp1sym);
        end

        function poles = LH_to_BN(obj)
            % Maps LP and HP poles to BP and NP poles
            b = (obj.wp2-obj.wp1)/obj.CF;
            poles1 = b * obj.protoFilter.poles / 2 + sqrt(((b*obj.protoFilter.poles).^2)./4 - 1);
            poles2 = b * obj.protoFilter.poles / 2 - sqrt(((b*obj.protoFilter.poles).^2)./4 - 1);
            poles = obj.CF * [poles1, poles2]; % Ensures poles are not normalized
        end
    end
end