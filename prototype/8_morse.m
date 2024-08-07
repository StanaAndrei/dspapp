clc
load data.mat

%decode sound to morse

	%your code goes here!!!
[input, fs] = audioread('morseCode4.wav');
figure;
t=(0:length(input)-1)/fs;
plot(t, input);
xlabel('time');
ylabel('amplitude');

mCode = '';
nr = 0;
nr0 = 0;
for i=2:length(input)
    %disp(input(i));
    if (input(i) == 0)
       nr0 = nr0 + 1;
    else
        if (nr0 > 30000)
           mCode = [mCode, '/'];
        end
        if (nr0 > 13000)
            mCode = [mCode, ' '];
        end
        
        nr0 = 0;
    end
    
    if (input(i) ~= 0)
        nr = nr + 1;
    else
        if (nr ~= 0)
            if (nr > 13000)
                mCode = [mCode, '-'];
            end
            if (nr < 5000)
                mCode = [mCode, '.'];
            end
        end
        nr = 0;
    end
end
disp('ads')
disp(mCode)

%mCode = '-.. ... .--. .-.. .- -... ... ';

deco = [];
mCode = [mCode ' '];	%mCode is an array containing the morse characters to be decoded to text
lCode = [];

for j=1:length(mCode)
    if(strcmp(mCode(j),' ') || strcmp(mCode(j),'/'))
        for i=double('a'):double('z')
            letter = getfield(morse,char(i));
            if strcmp(lCode, letter)
                deco = [deco, char(i)];
            end
        end
        for i=0:9
            numb = getfield(morse,['nr',num2str(i)]);
            if strcmp(lCode, numb)
                deco = [deco, num2str(i)];
            end
        end
        lCode = [];
    else
        lCode = [lCode mCode(j)];
    end
    if strcmp(mCode(j),'/')
        deco = [deco, ' '];
    end
end

fprintf('Decode : %s \n', deco);