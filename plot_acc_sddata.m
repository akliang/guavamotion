
set(0,'DefaultTextInterpreter','none');

fname='/Users/moonbeam/Desktop/g_test/2g_64ms_throw.TXT';
[p f e]=fileparts(fname);

q=load(fname);

c.unixtime=1;
c.timestamp=2;
c.milli=3;
c.x=4;
c.y=5;
c.z=6;

fh=subplot(4,1,1)
plot(q(:,c.milli),q(:,c.x))
title(sprintf('%s\nwalking straight line\nx accel',fname))
subplot(4,1,2)
plot(q(:,c.milli),q(:,c.y))
title('y accel')
subplot(4,1,3)
plot(q(:,c.milli),q(:,c.z))
title('z accel');
xlabel('time (ms)')
subplot(4,1,4)
hist(diff(q(:,c.milli)),200)
title('histogram of time between reads');
xlabel('time between reads (ms)');
ylabel('count');


print([f '.png'],'-dpng');