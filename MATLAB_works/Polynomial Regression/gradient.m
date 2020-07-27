function out=gradient(d,x,deg)
    out=zeros(1+deg);
    for i=0:deg
       out(i+1)=sum((x.^i).*d);
    end
end