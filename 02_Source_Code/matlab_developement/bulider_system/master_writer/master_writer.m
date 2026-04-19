classdef master_writer < matlab.System ...
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
        slave_address = uint16(60);
        bus_frequency = uint64(100000);
    end

    properties (Access = private)


    end

    methods
        % Constructor
        function obj = master_writer(varargin)
            setProperties(obj,nargin,varargin{:});
        end
    end

    methods (Access=protected)
        function setupImpl(obj)
            if ~coder.target('MATLAB')
                coder.cinclude('master_writer.h');
                coder.ceval('setupFunctionmaster_writer', (obj.slave_address),1, (obj.bus_frequency),1);
            end
        end

        function validateInputsImpl(obj,varargin)
            %  Check the input size
            if nargin ~=0

                validateattributes(varargin{1},{'double'},{'2d','size',[1,1]},'','local_lat');
                validateattributes(varargin{2},{'logical'},{'2d','size',[1,1]},'','local_lat_isValid');
                validateattributes(varargin{3},{'double'},{'2d','size',[1,1]},'','local_lng');
                validateattributes(varargin{4},{'logical'},{'2d','size',[1,1]},'','local_lng_inValid');
                validateattributes(varargin{5},{'double'},{'2d','size',[1,1]},'','local_speed');
                validateattributes(varargin{6},{'logical'},{'2d','size',[1,1]},'','local_speed_isValid');
                validateattributes(varargin{7},{'logical'},{'2d','size',[1,1]},'','TRANSMITTING');

            end
        end

        function WRITING_ACK = stepImpl(obj ,local_lat,local_lat_isValid,local_lng,local_lng_inValid,local_speed,local_speed_isValid,TRANSMITTING)
            WRITING_ACK = boolean(zeros(1,1));

            if isempty(coder.target)
            else
                coder.ceval('stepFunctionmaster_writer',coder.ref(WRITING_ACK),1, local_lat,1, local_lat_isValid,1, local_lng,1, local_lng_inValid,1, local_speed,1, local_speed_isValid,1, TRANSMITTING,1);
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
            num = 7;
        end

        function num = getNumOutputsImpl(~)
            num = 1;
        end

        function varargout = getInputNamesImpl(obj)
            varargout{1} = 'local_lat';
            varargout{2} = 'local_lat_isValid';
            varargout{3} = 'local_lng';
            varargout{4} = 'local_lng_inValid';
            varargout{5} = 'local_speed';
            varargout{6} = 'local_speed_isValid';
            varargout{7} = 'TRANSMITTING';

        end

        function varargout = getOutputNamesImpl(obj)
            varargout{1} = 'WRITING_ACK';
        end

        function flag = isOutputSizeLockedImpl(~,~)
            flag = true;
        end

        function varargout = isOutputFixedSizeImpl(~,~)
            varargout{1} = true;
        end

        function varargout = isOutputComplexImpl(~)
            varargout{1} = false;
        end

        function varargout = getOutputSizeImpl(~)
            varargout{1} = [1,1];
        end

        function varargout = getOutputDataTypeImpl(~)
            varargout{1} = 'boolean';
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
            icon = 'master_writer';
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
            name = 'master_writer';
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


            buildInfo.addIncludePaths('C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\bulider_system\master_writer');
            addSourceFiles(buildInfo,'master_writer.cpp','C:\Users\Nitesh\Documents\GitHubDump\ZigBee_Major_Project\matlab_developement\bulider_system\master_writer');

        end
    end
end
