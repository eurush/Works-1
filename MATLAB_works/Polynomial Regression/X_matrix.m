function out=X_matrix(w,x)
        out=zeros(length(x));
        for i=0:(length(w)-1)
            out(i+1,:)=w(i+1)*(x.^i);
        end
        out=sum(out);
end