CenterFrequencies = [31.5, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000];
qualityFactor = 1.4;
Fs = 44100;
normalizedCenterFrequencies = 2 * centerFrequencies / Fs;

cutoffFrequencies = normalizedCenterFrequencies*(-1/(2*qualityFactor) + sqrt(1+1/(4*qualityFactor ^ 2)));
normalizedCutoffFrequencies = 2 * cutoffFrequencies / Fs;
[H, F] = freqz(fir1(50, normalizedCutoffFrequencies(10), 'high'));
subplot(2, 1, 1);
plot(F, abs(H), 'DisplayName', sprintf('Cutoff low Freq = %d Hz', cutoffFrequencies(1)));
hold on;
sum =abs(H);

cutoffFrequencies2 = normalizedCenterFrequencies*(1/(2*qualityFactor) + sqrt(1+1/(4*qualityFactor ^ 2)));
normalizedCutoffFrequencie2s = 2 * cutoffFrequencies2 / Fs;
[H, F] = freqz(fir1(50, cutoffFrequencies2(1), 'low'));
sum=sum+abs(H);
subplot(2, 1, 2);
plot(F, abs(H), 'DisplayName', sprintf('Cutoff high Freq = %d Hz', cutoffFrequencies2(10)));
hold on;


for i = 2:9
    [H, F] = freqz(fir1(50,[cutoffFrequencies(i),cutoffFrequencies2(i)] , 'bandpass'));
    subplot(2, 1, 1);
    plot(F, abs(H), 'DisplayName', sprintf('Center Freq = %d Hz', CenterFrequencies(i)));
    hold on;
    sum = sum + abs(H);
end

subplot(2, 1, 1);
title('Individual Filter Responses');
xlabel('Frequency(Hz)');
ylabel('Magnitude');
legend;
grid on;

subplot(2, 1, 2);
plot(F, abs(sum));
title('Sum of Filter Responses');
xlabel('Frequency(Hz)');
ylabel('Magnitude');
grid on;

hold off;