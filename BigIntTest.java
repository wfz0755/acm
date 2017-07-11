import java.math.BigInteger;
import java.util.*;

class BigIntTest{
	public static void main(String[] args)
	{
		Scanner sc=  new Scanner(System.in);
		int caseNo;
		caseNo = sc.nextInt();
		while(caseNo-- != 0)
		{

			int n = sc.nextInt();
			BigInteger sum = BigInteger.valueOf(1);
			BigInteger v1 = BigInteger.valueOf(n);
			v1 = v1.multiply(v1.subtract(BigInteger.ONE));
			v1 = v1.divide(BigInteger.valueOf(2));
			sum = sum.add(v1);
			BigInteger v2 = BigInteger.valueOf(n);
			BigInteger v3 = BigInteger.valueOf(n);
			
			for(int i = 1; i<= 3; i++)
			{
				v3 = v3.multiply(v2.subtract(BigInteger.valueOf(i)));
				//		System.out.println("rua: v3 = " v3);
				
			}
			v3 = v3.divide(BigInteger.valueOf(24));
			sum = sum.add(v3);
			System.out.println(sum);
		}
	}


}
