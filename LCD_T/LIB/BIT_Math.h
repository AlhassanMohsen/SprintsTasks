#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT) 	 (REG |= (1<<BIT))
#define CLR_BIT(REG,BIT) 	 (REG &=~ (1<<BIT))
#define Toggle_BIT(REG,BIT)  (REG ^= (1<<BIT))
#define GET_BIT(REG,BIT) 	 ((REG >> BIT) & (0X01))
#define abs(x,y)			 (x > y? x - y : y - x)
#endif /* BIT_MATH_H_ */
