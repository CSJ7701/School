function Fspecs(name)
% Wrapper script for general filter design

while ~exist('name','var') % Checks whether NAME argument was passed. 
    disp('Please enter problem name');
    name=input(':   ','s');
end

% Initial Prompt
disp('+------------------------+');
disp('|   Filter Information   |');
disp('|------------------------|');
disp('|      HP/LP/BP/NP       |');
disp('|      Butter/Chevy      |');
disp('|      Ana/Dig           |');
disp('+------------------------+');

type=input(':  ', 's'); % Saves general filter info to TYPE

%% Prompt
topline='Enter Parameters';
if contains(type,["lp","hp"],'IgnoreCase',true)
    variableline='Amax,Amin,Wp,Ws,Units'; % Specifies variables needed for lp/hp
elseif contains(type,["bp","np"],"IgnoreCase",true)
    variableline='Amax,Amin,Wp1,Wp2,Ws1,Ws2,Units'; % Specifies variables needed for bp/np
end

if contains(type,"ana",'IgnoreCase',true)
    unitsline='Units - Hz or R/S'; % Specifies units needed for analog
elseif contains(type,"dig","IgnoreCase",true)
    unitsline='Units - Hz or frac (Fractions of sampling frequency)'; % Specifies units needed for digital
    variableline=strcat(variableline,',Fs'); % If digital, adds an extra (optional) variable to the end of the var prompt line
end

printFilterParameters(topline,variableline,unitsline) % Custom prompt function
data=input(':   ','s'); % Saves spec. data to DATA
params=strsplit(data, ','); % Splits DATA into an array (PARAMS) at each comma
%% Assign Data
dig=0; % Default. Specifies whether its a digital filter.
if contains(type,["lp","hp"],'IgnoreCase',true)
    Wp1=0;
    Ws1=0; % Sets wp1 and ws1 to 0, they are unused in LP and HP
    Amax=str2double(params{1}); 
    Amin=str2double(params{2});
    if contains(data,"hz",'IgnoreCase',true)
        Wp2=2*pi*str2double(params{3}); 
        Ws2=2*pi*str2double(params{4}); % Converts from HZ
    elseif contains(data,"r/s",'IgnoreCase',true)
        Wp2=str2double(params{3});
        Ws2=str2double(params{4});
    end
    if contains(type,'lp','IgnoreCase',true)
        ftype='LP';
    elseif contains(type,'HP','IgnoreCase',true)
        ftype='HP';
    end % Sets the type as a string to pass to object function

    if contains(type,'dig','IgnoreCase',true)
        if (length(params)==6)
            Fs=str2double(params{6}); % Sets sampling frequency if it was passed 
        end

        if contains(data,'hz','IgnoreCase',true)
            Ws2=Ws2/Fs;
            Wp2=Wp2/Fs; % Finds frequencies as fractions of sampling frequency
        elseif contains(data,'frac','IgnoreCase',true)
            Wp2=str2double(params{3});
            Ws2=str2double(params{4});
        end
        Ws2=Digital.Prewarp(Ws2);
        Wp2=Digital.Prewarp(Wp2); % Prewarps if digital (remember from earlier, ws1 and wp1 are unused for lp/hp)

        if contains(data,'hz','IgnoreCase',true)
            Ws2=(Ws2/2*pi)*Fs;
            Wp2=(Wp2/2*pi)*Fs; % Transforms frequencies if passed in HZ
            % Honestly not sure if this is right, but we never pass these
            % in HZ anyway.
        end
    end

elseif contains(type,["bp","np"],'IgnoreCase',true)
    Amax=str2double(params{1});
    Amin=str2double(params{2});
    if contains(data,"hz",'IgnoreCase',true)
        Wp1=2*pi*str2double(params{3});
        Wp2=2*pi*str2double(params{4});
        Ws1=2*pi*str2double(params{5});
        Ws2=2*pi*str2double(params{6});
    elseif contains(data,"r/s",'IgnoreCase',true)
        Wp1=str2double(params{3});
        Wp2=str2double(params{4});
        Ws1=str2double(params{5});
        Ws2=str2double(params{6});
    end
    if contains(type,'bp','IgnoreCase',true)
        ftype='BP';
    elseif contains(type,'np','IgnoreCase',true)
        ftype='NP';
    end

    if contains(type,'dig','IgnoreCase',true)
        dig=1;
        if (length(params)==8)
            Fs=str2double(params{8});
        elseif (length(params)==6)
            Fs=str2double(params{6});
        end

        if contains(type,'hz','IgnoreCase',true)
            Ws1=Ws1/Fs; Ws2=Ws2/Fs;
            Wp1=Wp1/Fs; Wp2=Wp2/Fs;
        elseif contains(data,'frac','IgnoreCase',true)
            Wp1=str2double(params{3});
            Wp2=str2double(params{4});
            Ws1=str2double(params{5});
            Ws2=str2double(params{6});
        end
        Ws1=Digital.Prewarp(Ws1); Ws2=Digital.Prewarp(Ws2);
        Wp1=Digital.Prewarp(Wp1); Wp2=Digital.Prewarp(Wp2);
        % Prewarp for Digital
        if contains(data,'hz','IgnoreCase',true)
            Ws1=(Ws1/2*pi)*Fs; Ws2=(Ws2/2*pi)*Fs;
            Wp1=(Wp1/2*pi)*Fs; Wp2=(Wp2/2*pi)*Fs;
        end
    end
end
%% Make Object
if contains(type,"Butter",'IgnoreCase',true)
    filter=Butter(Amax,Amin,Wp1,Wp2,Ws1,Ws2,ftype,0,dig);
    % Create butterworth filter using numbers from earlier
elseif contains(type,"Chevy","IgnoreCase",true)
    filter=Chevy(Amax,Amin,Wp1,Wp2,Ws1,Ws2,ftype,0,dig);
    % Create chebyshev filter using numbers from earlier
end
if contains(type,'dig','IgnoreCase',true)
    if ((filter.typenum<3)&&(contains(type,'chevy','IgnoreCase',true)))
        filter.poles=filter.wp.*filter.poles;
        % Chebyshev HP/LP Digital, multiply poles by wp.
    elseif (filter.typenum>2)
        %filter.poles=filter.CF.*filter.poles;
        % This was wrong. I'm leaving it here to help remind me to tell
        % other people to do this, since I do it elsewhere.
    end
    disp(filter.poles);
    filter.poles=Digital.Bilin(filter.poles);
    % Take bilinear transform of the poles after they are properly
    % calcualted.
    filter.DigDisplay;
    % Display the digital coefficients if its a digital filter.
end

% Add to workspace
assignin('base',name,filter);
%% Print Function
    function printFilterParameters(titleLine, parameterLine, unitsLine)
        % Set a common width for both printouts
        lineWidth = max((length(unitsLine) + 4),(length(parameterLine) + 4));

        % Print the title line
        disp(['+', repelem('-', lineWidth-2), '+']);
        disp(['|', pad(titleLine, lineWidth-2, 'both'), '|']);
        disp(['+', repelem('-', lineWidth-2), '+']);

        % Print the parameter line
        disp(['|', pad(parameterLine, lineWidth-2, 'both'), '|']);

        % Print the units line
        disp(['|', pad(unitsLine, lineWidth-2, 'both'), '|']);

        % Print the bottom border
        disp(['+', repelem('-', lineWidth-2), '+']);
    end
end