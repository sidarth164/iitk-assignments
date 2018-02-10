// foo ()
// {
//     int i = 1;
// }

// int main(){
//     foo();
//     return 0;
// }

using System;

public class Test
{
	void foo(){
		int i=1;
	}
	public void Main()
	{
		Test t = new Test();
		t.foo();

	}
}