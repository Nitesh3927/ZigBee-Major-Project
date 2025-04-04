classdef gps_reader < matlab.System ...
        & coder.ExternalDependency ...
        & matlabshared.sensors.simulink.internal.BlockSampleTime

    %
    %#codegen
    %#ok<*EMCA>

    properties

    end

    properties(Access = protected)
        Logo = 'IO Device Builder';
    end

    properties (Nontunable)

    end

    properties (Access = private)


    end

    methods
        % Constructor
        function obj = gps_reader(varargin)
            setProperties(obj,nargin,varargin{:});
        end
    end

    methods (Access=protected)
        function setupImpl(obj)
            if ~coder.target('MATLAB')
                coder.cinclude('gps_reader.h');
                coder.ceval('setupFunctiongps_reader');
            end
        end

        function validateInputsImpl(obj,varargin)
            %  Check the input size
            if nargin ~=0



            end
        end

        function [hdop,hdop_isValid,satellite,satellite_isValid,time_hours,time_mins,time_sec,time_isValid,date_day,date_month,date_year,date_isValid,speed,speed_isValid,lat,lat_isValid,lng,lng_isValid] = stepImpl(obj)
            hdop = double(zeros(1,1));
            hdop_isValid = boolean(zeros(1,1));
            satellite = uint8(zeros(1,1));
            satellite_isValid = boolean(zeros(1,1));
            time_hours = uint8(zeros(1,1));
            time_mins = uint8(zeros(1,1));
            time_sec = uint8(zeros(1,1));
            time_isValid = boolean(zeros(1,1));
            date_day = uint8(zeros(1,1));
            date_month = uint8(zeros(1,1));
            date_year = uint16(zeros(1,1));
            date_isValid = boolean(zeros(1,1));
            speed = double(zeros(1,1));
            speed_isValid = boolean(zeros(1,1));
            lat = double(zeros(1,1));
            lat_isValid = boolean(zeros(1,1));
            lng = double(zeros(1,1));
            lng_isValid = boolean(zeros(1,1));
            if isempty(coder.target)
            else
                coder.ceval('stepFunctiongps_reader',coder.ref(hdop),1,coder.ref(hdop_isValid),1,coder.ref(satellite),1,coder.ref(satellite_isValid),1,coder.ref(time_hours),1,coder.ref(time_mins),1,coder.ref(time_sec),1,coder.ref(time_isValid),1,coder.ref(date_day),1,coder.ref(date_month),1,coder.ref(date_year),1,coder.ref(date_isValid),1,coder.ref(speed),1,coder.ref(speed_isValid),1,coder.ref(lat),1,coder.ref(lat_isValid),1,coder.ref(lng),1,coder.ref(lng_isValid),1);
            end
        end

        function releaseImpl(obj)
            if isempty(coder.target)
            else

            end
        end
    end

    methods (Access=protected)
        %% Define output properties
        function num = getNumInputsImpl(~)
            num = 0;
        end

        function num = getNumOutputsImpl(~)
            num = 18;
        end

        function varargout = getInputNamesImpl(obj)

        end

        function varargout = getOutputNamesImpl(obj)
            varargout{1} = 'hdop';
            varargout{2} = 'hdop_isValid';
            varargout{3} = 'satellite';
            varargout{4} = 'satellite_isValid';
            varargout{5} = 'time_hours';
            varargout{6} = 'time_mins';
            varargout{7} = 'time_sec';
            varargout{8} = 'time_isValid';
            varargout{9} = 'date_day';
            varargout{10} = 'date_month';
            varargout{11} = 'date_year';
            varargout{12} = 'date_isValid';
            varargout{13} = 'speed';
            varargout{14} = 'speed_isValid';
            varargout{15} = 'lat';
            varargout{16} = 'lat_isValid';
            varargout{17} = 'lng';
            varargout{18} = 'lng_isValid';
        end

        function flag = isOutputSizeLockedImpl(~,~)
            flag = true;
        end

        function varargout = isOutputFixedSizeImpl(~,~)
            varargout{1} = true;
            varargout{2} = true;
            varargout{3} = true;
            varargout{4} = true;
            varargout{5} = true;
            varargout{6} = true;
            varargout{7} = true;
            varargout{8} = true;
            varargout{9} = true;
            varargout{10} = true;
            varargout{11} = true;
            varargout{12} = true;
            varargout{13} = true;
            varargout{14} = true;
            varargout{15} = true;
            varargout{16} = true;
            varargout{17} = true;
            varargout{18} = true;
        end

        function varargout = isOutputComplexImpl(~)
            varargout{1} = false;
            varargout{2} = false;
            varargout{3} = false;
            varargout{4} = false;
            varargout{5} = false;
            varargout{6} = false;
            varargout{7} = false;
            varargout{8} = false;
            varargout{9} = false;
            varargout{10} = false;
            varargout{11} = false;
            varargout{12} = false;
            varargout{13} = false;
            varargout{14} = false;
            varargout{15} = false;
            varargout{16} = false;
            varargout{17} = false;
            varargout{18} = false;
        end

        function varargout = getOutputSizeImpl(~)
            varargout{1} = [1,1];
            varargout{2} = [1,1];
            varargout{3} = [1,1];
            varargout{4} = [1,1];
            varargout{5} = [1,1];
            varargout{6} = [1,1];
            varargout{7} = [1,1];
            varargout{8} = [1,1];
            varargout{9} = [1,1];
            varargout{10} = [1,1];
            varargout{11} = [1,1];
            varargout{12} = [1,1];
            varargout{13} = [1,1];
            varargout{14} = [1,1];
            varargout{15} = [1,1];
            varargout{16} = [1,1];
            varargout{17} = [1,1];
            varargout{18} = [1,1];
        end

        function varargout = getOutputDataTypeImpl(~)
            varargout{1} = 'double';
            varargout{2} = 'boolean';
            varargout{3} = 'uint8';
            varargout{4} = 'boolean';
            varargout{5} = 'uint8';
            varargout{6} = 'uint8';
            varargout{7} = 'uint8';
            varargout{8} = 'boolean';
            varargout{9} = 'uint8';
            varargout{10} = 'uint8';
            varargout{11} = 'uint16';
            varargout{12} = 'boolean';
            varargout{13} = 'double';
            varargout{14} = 'boolean';
            varargout{15} = 'double';
            varargout{16} = 'boolean';
            varargout{17} = 'double';
            varargout{18} = 'boolean';
        end

        function maskDisplayCmds = getMaskDisplayImpl(obj)
            outport_label = [];
            num = getNumOutputsImpl(obj);
            if num > 0
                outputs = cell(1,num);
                [outputs{1:num}] = getOutputNamesImpl(obj);
                for i = 1:num
                    outport_label = [outport_label 'port_label(''output'',' num2str(i) ',''' outputs{i} ''');' ]; %#ok<AGROW>
                end
            end
            inport_label = [];
            num = getNumInputsImpl(obj);
            if num > 0
                inputs = cell(1,num);
                [inputs{1:num}] = getInputNamesImpl(obj);
                for i = 1:num
                    inport_label = [inport_label 'port_label(''input'',' num2str(i) ',''' inputs{i} ''');' ]; %#ok<AGROW>
                end
            end
            icon = 'gps_reader';
            maskDisplayCmds = [ ...
                ['color(''white'');',...
                'plot([100,100,100,100]*1,[100,100,100,100]*1);',...
                'plot([100,100,100,100]*0,[100,100,100,100]*0);',...
                'color(''blue'');', ...
                ['text(38, 92, ','''',obj.Logo,'''',',''horizontalAlignment'', ''right'');',newline],...
                'color(''black'');'], ...
                ['text(52,50,' [''' ' icon ''',''horizontalAlignment'',''center'');' newline]]   ...
                inport_label ...
                outport_label
                ];
        end

        function sts = getSampleTimeImpl(obj)
            sts = getSampleTimeImpl@matlabshared.sensors.simulink.internal.BlockSampleTime(obj);
        end
    end

    methods (Static, Access=protected)
        function simMode = getSimulateUsingImpl(~)
            simMode = 'Interpreted execution';
        end

        function isVisible = showSimulateUsingImpl
            isVisible = false;
        end
    end

    methods (Static)
        function name = getDescriptiveName(~)
            name = 'gps_reader';
        end

        function tf = isSupportedContext(~)
            tf = true;
        end

        function updateBuildInfo(buildInfo, context)
            coder.extrinsic('codertarget.targethardware.getTargetHardware');
            hCS = coder.const(getActiveConfigSet(bdroot));
            targetInfo = coder.const(codertarget.targethardware.getTargetHardware(hCS));

            % Added this env variable to fetch the comm libraries required only for Arduino target.
            % The env variable is cleared at the end of
            % "GenerateWrapperMakefile.m" file.
            if contains(targetInfo.TargetName,'arduinotarget')
                setenv('Arduino_ML_Codegen_I2C', 'Y');
            end

            buildInfo.addIncludePaths('C:\Users\Nitesh\Documents\Arduino\libraries\TinyGPSPlus-ESP32\src');

            buildInfo.addIncludePaths('C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\gps_direct\gps_reader');
            addSourceFiles(buildInfo,'TinyGPSPlus.cpp','C:\Users\Nitesh\Documents\Arduino\libraries\TinyGPSPlus-ESP32\src');
            addSourceFiles(buildInfo,'gps_reader.cpp','C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\gps_direct\gps_reader');

        end
    end
end
