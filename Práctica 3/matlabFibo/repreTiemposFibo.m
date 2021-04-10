clear all
clf
t=load('tiemposFibonacciRecursivo.txt'); %Carga en memoria el fichero
x=t(:,1); %Eje x: n, primera columna
y=t(:,2); %Eje y: tiempos t(n), segunda columna
plot(x,y, '-*'); %Representaci�n gr�fica y frente a x
title('Experimentaci�n tiempos Fibonacci recursivo');
xlabel('n'); %Etiqueta del eje x
ylabel('t(n) (tics de reloj)'); %Etiqueta del eje y
