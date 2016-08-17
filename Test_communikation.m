function [] = Test_communikation(V,Kp,Ti,Td,dT)
s = serial('COM14', 'BaudRate', 115200,'DataBits',8);
fopen(s);
%pause(0.5);

flushinput(s);


N=150;

V=40;
Kp=23;
Ti=142;
Td=35;
dT=10;
Start=1;

PWMvalue=zeros(1,N);
errorValue=zeros(1,N);
Distance=zeros(1,N);
tid =1:N;
%pause(0.2);
allValues=[uint8(Start),uint8(V),uint8(Kp),uint8(Ti),uint8(Td),uint8(dT)];


%pause(0.2);
for p = 1:6
flushinput(s);
flushoutput(s);
fwrite(s,allValues(p),'uint8');
flushinput(s);
flushoutput(s);
pause(0.5);
end

pause(0.2);
for k=1:N

flushinput(s);
flushoutput(s);

fwrite(s,'1')
PWMvalue(k)=str2double(fscanf(s,'%c'))

flushinput(s);
flushoutput(s);

fwrite(s,'2')
errorValue(k)=str2double(fscanf(s,'%c'))
flushinput(s);
flushoutput(s);

fwrite(s,'3')
Distance(k)=str2double(fscanf(s,'%c'));
flushinput(s);
flushoutput(s);

pause(0.2);

plot(tid,PWMvalue,'k',tid,errorValue,'r-',tid,Distance,'g')
axis([0,100,-150,150]);
 xlabel('samples')
 ylabel('Utsignal')
 title('Pingis-Projekt')
 legend('PWMvalue','ErrorValue','Distance')

 end
 fclose(instrfind);
 delete(instrfind);
end
 