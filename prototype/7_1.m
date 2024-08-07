inputFile = 'input.wav';
gains = [0, 3, -6, 9, 0, -12, 6, 0, -9, 12];
outputFile = 'output.wav';

equalizer(inputFile, gains, outputFile);


function equalizer(inputFile, gains, outputFile)
    [x, fs] = audioread(inputFile);

    plotSpectrum(x, fs, 'Input Spectrum');

    centerFreqs = [31.5, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000];
    filters = cell(1, 10);

    for i = 1:10
        f1 = centerFreqs(i) / (fs/2);
        f2 = centerFreqs(i+1) / (fs/2);
        filters{i} = fir1(100, [f1 f2], 'band');
    end

    filteredSignals = cell(1, 10);

    for i = 1:10
        filteredSignals{i} = filter(filters{i}, 1, x);
    end

    for i = 1:10
        filteredSignals{i} = filteredSignals{i} * 10^(gains(i)/20);
    end

    y = sum(cell2mat(filteredSignals), 2);

    plotSpectrum(y, fs, 'Output Spectrum');

    audiowrite(outputFile, y, fs);
end

function plotSpectrum(x, fs, titleText)
    N = length(x);
    f = (-N/2:N/2-1) * fs/N;

    figure;
    subplot(2, 1, 1);
    plot(f, fftshift(abs(fft(x))));
    title('Magnitude Spectrum - Before Equalization');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');

    subplot(2, 1, 2);
    plot(f, fftshift(abs(fft(x))));
    title(titleText);
    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
end