ringModulation('input.wav', 'output.wav', 100);

function ringModulation(inputFilePath, outputFilePath, modulatorFrequency)
    [inputWave, sampleRate] = audioread(inputFilePath);
    
    t = (0:length(inputWave) - 1) / sampleRate;
    modulator = sin(2 * pi * modulatorFrequency * t)';
    
    outputWave = inputWave .* modulator;
    
    audiowrite(outputFilePath, outputWave, sampleRate);
    
    figure;
    subplot(3, 1, 1);
    plot(t(1:1000), inputWave(1:1000));
    title('Input Wave');
    
    subplot(3, 1, 2);
    plot(t(1:1000), outputWave(1:1000));
    title('Output Wave (Ring Modulated)');
    
    subplot(3, 1, 3);
    plot(t(1:1000), modulator(1:1000));
    title('Modulator Signal');
end
