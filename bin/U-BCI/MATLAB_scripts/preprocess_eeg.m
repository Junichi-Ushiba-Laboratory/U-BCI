function [results, user_data] = preprocess_eeg(stream_data_struct_array, user_data)
% It preprocesses the EEG data.
% You cannot change the number of channels.
%
% [Input]
% stream_data_struct_array: Array of stream data structure.
%   In this function, it uses the first component in EEG stream data.
%   Stream data structure includes the fields that is listed bellow.
%   time_series: <Channels specified in used_channel_num_list> x <Number of Sample>。
%   time_stamps: time data that corresponds to time_series (sec).
%   used_channel_num_list: List of using channel number.
% user_data: User defined structure.
%   It uses the after it adds and update custom data to the field.
%
% [Output]
% results: Array that has stores the preprocessed streaming data to the first component.
%   Stream data structure includes the fields that is listed bellow.
%   time_series: <Channels specified in used_channel_num_list> x <Number of Sample>。
%   time_stamps: time data that corresponds to time series data (sec).
% user_data: User defined structure

% Returns the streaming data directly.
results = [];
if (~isempty(stream_data_struct_array(1).time_series))
    results(1).time_series = stream_data_struct_array(1).time_series;
    results(1).time_stamps = stream_data_struct_array(1).time_stamps;

	% In user defined data, it uses the user_data structure in the workspace.
    % Or it uses the persistent variable to call the funtcion.

    % user_data.count = user_data.count + 1;
end

end
