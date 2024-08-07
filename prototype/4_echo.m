addEcho('input.wav', 'output-with-feedback.wav', 6000)

function addEcho(inputWavefile, outputWavefile, circularBuffSize)
    [inputSignal, sampleRate] = audioread(inputWavefile);
    circularBuffer = zeros(circularBuffSize, size(inputSignal, 2));
    bufferIndex = uint32(1);
    circularBuffer2 = zeros(circularBuffSize, size(inputSignal, 2));
    gain = 0.5;
    gainFB = 0.5;
    outputSignal = zeros(size(inputSignal));
    
    for i = 1:size(inputSignal, 2)
        for j = 1:size(inputSignal, 1)
            delayedSample = circularBuffer(bufferIndex, i);
            delaySample2 = circularBuffer2(bufferIndex, i);
            %outputSignal(j, i) = inputSignal(j, i) + gain*delayedSample;
            outputSignal(j, i) = gainFB*delaySample2 + inputSignal(j, i) + (gain - gainFB)*delayedSample;
            circularBuffer(bufferIndex, i) = inputSignal(j, i);
            circularBuffer2(bufferIndex, i) = outputSignal(j, i);
            
            bufferIndex = bufferIndex + 1;
            if bufferIndex > circularBuffSize
                bufferIndex = uint32(1);
            end
        end
    end
    audiowrite(outputWavefile, outputSignal, sampleRate);
    
    figure;
    
    subplot(2, 1, 1);
    plot(inputSignal);
    title('input');
    
    subplot(2, 1, 2);
    plot(outputSignal);
    title('output');
end


%pentru sample-ul cu valoarea Buffer-ului de 6000 exista un ecou mult mai
%ridicat si accentuat fata de sample-ul cu valoarea Buffer-ului de 2000