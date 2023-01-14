#include "bitset.h"

namespace ddd {
  void bitset_test0()
  {
    printf(" ############################## bitset_test0() ############################## \n\n");
    PrintBuiltInTypeSize();
    printf("\n");
    
    {
      ddd::Bitset<10>  test0{10};
      ddd::Bitset<32>  test1{-10};
      ddd::Bitset<64>  test2{long(-10)};
      ddd::Bitset<64>  test3{-10};
      ddd::Bitset<200> test4{10};
      ddd::Bitset<100> test5{10.0f};
      ddd::Bitset<100> test6{-10.0f};
      ddd::Bitset<100> test7{10.0};
      ddd::Bitset<100> test8{-10.0};
    
      std::cout << "Bitset test:" << std::endl;
      std::cout << "test0 \n" << test0 << std::endl;
      std::cout << "test1 \n" << test1 << std::endl;
      std::cout << "test2 \n" << test2 << std::endl;
      std::cout << "test3 \n" << test3 << std::endl;
      std::cout << "test4 \n" << test4 << std::endl;
      std::cout << "test5 \n" << test5 << std::endl;
      std::cout << "test6 \n" << test6 << std::endl;
      std::cout << "test7 \n" << test7 << std::endl;
      std::cout << "test8 \n" << test8 << std::endl;
      std::cout << std::endl;
    }
    
    {
      ddd::TriBitset<10>  test0{10};
      ddd::TriBitset<32>  test1{-10};
      ddd::TriBitset<64>  test2{long(-10)};
      ddd::TriBitset<64>  test3{-10};
      ddd::TriBitset<200> test4{10};
      ddd::TriBitset<100> test5{10.0f};
      ddd::TriBitset<100> test6{-10.0f};
      ddd::TriBitset<100> test7{10.0};
      ddd::TriBitset<100> test8{-10.0};
    
      std::cout << "TriBitset test:" << std::endl;
      std::cout << "test0 \n" << test0 << std::endl;
      std::cout << "test1 \n" << test1 << std::endl;
      std::cout << "test2 \n" << test2 << std::endl;
      std::cout << "test3 \n" << test3 << std::endl;
      std::cout << "test4 \n" << test4 << std::endl;
      std::cout << "test5 \n" << test5 << std::endl;
      std::cout << "test6 \n" << test6 << std::endl;
      std::cout << "test7 \n" << test7 << std::endl;
      std::cout << "test8 \n" << test8 << std::endl;
      std::cout << std::endl;
    }
    
    
    printf("\n");
    
    printf("unsigned:      %u\n", ConvertToDecimal<unsigned>(ConvertToBinary(10).c_str()));
    printf("int:           %d\n", ConvertToDecimal<int>(ConvertToBinary(-10).c_str()));
    printf("float:         %f\n", ConvertToDecimal<float>(ConvertToBinary(10.0f).c_str()));
    printf("-float:        %f\n", ConvertToDecimal<float>(ConvertToBinary(-10.0f).c_str()));
    printf("unsigned long: %lu\n", ConvertToDecimal<unsigned long>(ConvertToBinary(long(10)).c_str()));
    printf("long:          %ld\n", ConvertToDecimal<long>(ConvertToBinary(long(-10)).c_str()));
    printf("double:        %f\n", ConvertToDecimal<double>(ConvertToBinary(10.0).c_str()));
    printf("-double:       %f\n", ConvertToDecimal<double>(ConvertToBinary(-10.0).c_str()));
    
    printf("unsigned:      %s\n", ConvertToBinary(10).c_str());
    printf("int:           %s\n", ConvertToBinary(-10).c_str());
    printf("float:         %s\n", ConvertToBinary(10.0f).c_str());
    printf("-float:        %s\n", ConvertToBinary(-10.0f).c_str());
    printf("unsigned long: %s\n", ConvertToBinary(long(10)).c_str());
    printf("long:          %s\n", ConvertToBinary(long(-10)).c_str());
    printf("double:        %s\n", ConvertToBinary(10.0).c_str());
    printf("-double:       %s\n", ConvertToBinary(-10.0).c_str());
    
    printf("unsigned:      %s\n", ConvertToOct(10).c_str());
    printf("int:           %s\n", ConvertToOct(-10).c_str());
    printf("float:         %s\n", ConvertToOct(10.0f).c_str());
    printf("-float:        %s\n", ConvertToOct(-10.0f).c_str());
    printf("unsigned long: %s\n", ConvertToOct(long(10)).c_str());
    printf("long:          %s\n", ConvertToOct(long(-10)).c_str());
    printf("double:        %s\n", ConvertToOct(10.0).c_str());
    printf("-double:       %s\n", ConvertToOct(-10.0).c_str());
    
    printf("\n");
    printf("unsigned:      %s\n", ConvertToHex(10).c_str());
    printf("int:           %s\n", ConvertToHex(-10).c_str());
    printf("float:         %s\n", ConvertToHex(10.0f).c_str());
    printf("-float:        %s\n", ConvertToHex(-10.0f).c_str());
    printf("unsigned long: %s\n", ConvertToHex(long(10)).c_str());
    printf("long:          %s\n", ConvertToHex(long(-10)).c_str());
    printf("double:        %s\n", ConvertToHex(10.0).c_str());
    printf("-double:       %s\n", ConvertToHex(-10.0).c_str());
    
    printf("\n");
    printf("Base 2:       %s\n", ConvertToBase(2,  17).c_str());
    printf("Base 3:       %s\n", ConvertToBase(3,  17).c_str());
    printf("Base 3:       %s\n", ConvertToBase(3,  -17).c_str());
    printf("Base 3:       %s\n", ConvertToBase(3,  17.0f).c_str());
    printf("Base 3:       %s\n", ConvertToBase(3,  -17.0f).c_str());
    printf("Base 3:       %s\n", ConvertToBase(3,  17.0).c_str());
    printf("Base 3:       %s\n", ConvertToBase(3,  -17.0).c_str());
    printf("Base 4:       %s\n", ConvertToBase(4,  17).c_str());
    printf("Base 5:       %s\n", ConvertToBase(5,  17).c_str());
    printf("Base 6:       %s\n", ConvertToBase(6,  17).c_str());
    printf("Base 7:       %s\n", ConvertToBase(7,  17).c_str());
    printf("Base 8:       %s\n", ConvertToBase(8,  17).c_str());
    printf("Base 9:       %s\n", ConvertToBase(9,  17).c_str());
    printf("Base 10:      %s\n", ConvertToBase(10, 17).c_str());
    printf("Base 11:      %s\n", ConvertToBase(11, 17).c_str());
    printf("Base 12:      %s\n", ConvertToBase(12, 17).c_str());
    printf("Base 13:      %s\n", ConvertToBase(13, 17).c_str());
    printf("Base 14:      %s\n", ConvertToBase(14, 17).c_str());
    printf("Base 15:      %s\n", ConvertToBase(15, 17).c_str());
    printf("Base 16:      %s\n", ConvertToBase(16, 17).c_str());
    
    printf("\n");
    printf(" ############################## bitset_test0() ############################## \n");
  }
  
}

int main()
{
  ddd::bitset_test0();
}
