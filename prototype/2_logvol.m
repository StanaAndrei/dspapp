adjustVol('ghost.wav', -50, 'amp.wav');

function adjustVol(iFile, dbGain, oFile)
    if ~exist(iFile, 'file')
        error("File doesn't exists");
    end
    [audioIn, sr] = audioread(iFile);
    gainFactor = 10^(dbGain/20);
    audioOut = audioIn * gainFactor;
    audiowrite(oFile, audioOut, sr);
    
    t = (0:length(audioIn)-1) / sr;
    figure;
    
    subplot(2,1,1);
    plot(t, audioIn);
    title("input")
    xlabel('Time(s)')
    ylabel('Amplitude')
    
    subplot(2,1,2);
    plot(t, audioOut);
    title("output")
    xlabel('Time(s)')
    ylabel('Amplitude')
    
    disp('done')
end