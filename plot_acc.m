
fname='/Volumes/ACCELONE/ACC014.TXT';
[p f e]=fileparts(fname);

q=load(fname);

c.unixtime=1;
c.timestamp=2;
c.milli=3;
c.x=4;
c.y=5;
c.z=6;

fh=subplot(3,1,1)
plot(q(:,c.milli),q(:,c.x))
title(sprintf('%s\nwalking straight line\nx accel',fname))
subplot(3,1,2)
plot(q(:,c.milli),q(:,c.y))
title('y accel')
subplot(3,1,3)
plot(q(:,c.milli),q(:,c.z))
title('z accel');
xlabel('time (ms)')

print([f '.png'],'-dpng');