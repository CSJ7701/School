classdef Filter
    % Generic Parent Class
    % Used for inheritance into child filter classes

    properties
        % Given
        Amax
        Amin
        ftype

        % Calculated
        n
        rat
        poles
        w0
        Q

        % Background
        typenum
    end

    methods % Functions inherited by every filter
        function typenum=Ftype(obj)
            % Takes string description and transforms to numerical property
            % LP is 1, HP is 2, BP is 3 (BP-2=LP), NP is 4 (NP-2=HP)
            if (strcmpi(obj.ftype,"LP"))
                typenum=1;
            elseif (strcmpi(obj.ftype,"HP"))
                typenum=2;
            elseif (strcmpi(obj.ftype,"BP"))
                typenum=3;
            elseif (strcmpi(obj.ftype,"NP"))
                typenum=4;
            end
            return    
        end 
    end
end