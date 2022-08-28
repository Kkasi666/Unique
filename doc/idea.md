# 数据类型
## 根本数据类型 ：字节(byte)
```cpp
class Byte{
private:
	_byte value;
public:
	Byte();
	~Byte();
};
```
## 基本数据类型
### int
```
def int {
	size = byte.size * 8
}
```

## bool
```
def bool {
	size = byte.size
}
```

## char
```
def char {
	size = byte.size
}
```

## float
```
def float {
	size = byte.size * 4
	rule : {
		sign {
			size = 1 bit
		}
		exponent {
			size = byte.size
		}
		fraction {
			size = 23 bit
		}
		value = sign * fraction * exponent^2
	}
}
```