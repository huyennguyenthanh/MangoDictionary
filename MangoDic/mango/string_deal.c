#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *make_string_lower(char *input, char *to_deal){
	for(int i=0;i<strlen(to_deal);i++) 
		input[i] = tolower(to_deal[i]);
	input[strlen(to_deal)] = '\0';
	return input;
}

char *make_string_upper(char *input, char *to_deal){
	for(int i=0;i<strlen(to_deal);i++) 
		input[i] = toupper(to_deal[i]);
	input[strlen(to_deal)] = '\0';
	return input;
}

// void swap(char *ch1, char *ch2){
//   char temp = *ch1;
//   *ch1 = *ch2;
//   *ch2 = temp;
// }
// void trim_string(char input[]){
//   //trim (v): cắt tỉa, xén gọn.
//   char mark = input[strlen(input)];
//   for(int i=0;i<strlen(input)-1;i++){
//     if(isspace(input[i]) && isspace(input[i+1])){
//       int m = i, n = i+1;
//       while(isspace(input[m])) m++;
//       int flag = m;
//       while(isalpha(input[m]) || ispunct(input[m])) m++;
//       for(int j=flag;j<m;j++,n++) swap(&input[j],&input[n]);
//     }
//   }
// }

  
void xoa(char *s,int vitrixoa)
{
  int n=strlen(s);//gán n= độ dài của chuỗi
    for(int i=vitrixoa;i<n;i++)//duyệt chuỗi từ vị trí cần xóa
     s[i]=s[i+1];
  s[n-1]='\0'; //kết thúc
}
void xoa_khoang_trang(char * s)
{
    for(int i=0;i<strlen(s);i++)
    if(s[i]==' '&& s[i+1]==' ')
    {
      xoa(s,i);
      i--;
    }
    while(strlen(s) > 0 && s[0]==' ')xoa(s,0);
    while(strlen(s) > 0 && s[strlen(s)-1]==' ')xoa(s,strlen(s)-1);
}
 
void chuanhoa(char *a)
{
  xoa_khoang_trang(a);
  for (int i = 0; i < strlen(a); i++)
  {
    a[i] = tolower(a[i]);
  }
}
