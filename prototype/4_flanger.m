addEcho('input2.wav', 'output-with-flanger.wav', 2000, 6000, 0.5)

function addEcho(inputWavefile, outputWavefile, minBufferSize, maxBufferSize, modDepth)
    [inputSignal, sampleRate] = audioread(inputWavefile);
    bufferIndex = uint32(1);
    gain = 0.8;
    Fc=20;
    outputSignal = zeros(size(inputSignal));
    circularBuffer = zeros(maxBufferSize, 2);
    for i = 1:size(inputSignal, 1)
        pt=1 + modDepth*sin(2*pi*Fc/sampleRate * i);
        circularBuffSize = round((maxBufferSize - minBufferSize) * pt + minBufferSize);
        if (circularBuffSize > maxBufferSize)
           circularBuffSize = minBufferSize;
        end
        if (circularBuffSize < minBufferSize)
           circularBuffSize = maxBufferSize;
        end
        
        for j = 1:size(inputSignal, 2)
            delayedSample = circularBuffer(bufferIndex, j);
            outputSignal(i, j) = inputSignal(i, j) + gain*delayedSample;
            circularBuffer(bufferIndex, j) = inputSignal(i, j);
            
            bufferIndex = bufferIndex + 1;

            if(bufferIndex > circularBuffSize)
                bufferIndex = 1;
            end
            
            %disp(bufferIndex);
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