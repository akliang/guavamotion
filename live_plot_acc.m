
clear all;


% close the previous instance, if it exists
s1=instrfind('Status','open');
if (~isempty(s1))
  fclose(s1);
end

s1=serial('COM4');
fopen(s1);
c=onCleanup(@()fclose(s1));  % not working right now?


figure(1);
ph1=plot(1:10);
figure(2);
ph2=plot(1:10);
figure(3);
ph3=plot(1:10);

while true
    if (~exist('v','var'))
        v=zeros([1 7]);
        v(1,1)=now;
    else
        v(end+1,1)=now;
    end
    rdat=fscanf(s1);
    vars=regexp(rdat,',','split');
    v(end,2)=str2num(vars{1});  % accx
    v(end,3)=str2num(vars{2});  % accy
    v(end,4)=str2num(vars{3});  % accz
    v(end,5)=str2num(vars{4});  % angxz
    v(end,6)=str2num(vars{5});  % angyz
    v(end,7)=str2num(vars{6});  % angxy
    
    
    set(ph1,'Ydata',v(:,2),'Xdata',v(:,1));
    set(ph2,'Ydata',v(:,3),'Xdata',v(:,1));
    set(ph3,'Ydata',v(:,4),'Xdata',v(:,1));
    %set(fh,'Visible','on');
    
    pause(0.1);
end

