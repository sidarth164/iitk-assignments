package sample;

public class IOResult<T> {
    public T data;
    public Boolean ok;

    public IOResult(boolean ok, T data){
        this.ok=ok;
        this.data=data;
    }

    public boolean hasData(){
        return data!=null;
    }
}
