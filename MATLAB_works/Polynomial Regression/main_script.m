%% CLEARING SPACE 
clear;clc;
%% SETTING PSEUDO_DATA
x=linspace(1,100);
m=length(x);
x=(x-mean(x))/(std(x));
f=-4*x.*x.*x+4*x.*x+6*x+5+rand(1,m);
%% CONFIGURING OUR COST AND HYPOTHESIS FUNCTION 
degree=3;
w=rand(1,degree+1);
h=X_matrix(w,x);
j(1)=1./(2*m).*sum((f-h).^2);
err_min=1e-5;
err=1;
alp=0.4;    itr=1;
%% TRAINING LOOP
while (err>err_min)
%%  TUNING THE WEIGHTS OF N FEATURE COMPONENTS    
    h=X_matrix(w,x);
    w=w+alp.*(gradient(f-h,x,degree))./m;
    h=X_matrix(w,x);
    j(itr+1)=1./(2*m).*sum((f-h).^2);
    err=abs(j(itr+1)-j(itr));
    itr=itr+1;
%% PLOTTING REAL TIME     
    subplot(2,1,1);
    plot(x,f,'-o',x,h,'-*');
    xlabel('x');
    ylabel('y');
    legend({'ACTUAL DATA','OUR FIT'},'Location','northwest');
    drawnow;
    subplot(2,1,2);
    plot(1:itr,j(1:itr));
    xlabel('iterations'); ylabel('cost');
    drawnow;
end