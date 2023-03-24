
<font color="GREEN"> <b>1. Phân vùng nhớ</b> </font>

  -Trong vi điều khiển gồm 3 phân vùng bộ nhớ chính: ngoại vi, SRAM, Flash.

  -Flash là bộ nhớ có khả năng giữ lại dữ liệu đã được ghi khi không có điện. Do đó nó là nơi lưu chương trình.

  -RAM là bộ nhớ được sử dụng để lưu trữ dữ liệu tạm thời, dữ liệu sẽ bị mất khi không có điện. Ưu điểm của nó là tốc độ đọc ghi nhanh hơn nhiều so với các loại bộ nhớ khác nên nó là nơi thực thi chương trình.

  -Chương trình được lưu tại Flash sẽ được copy sang RAM để thực thi.

  -Trong RAM gồm 5 phân vùng nhớ:
		  
   + text: là bộ nhớ chỉ đọc, chứa các lệnh thực thi khi một chương trình được nạp vào RAM và các biến hằng(.rodata). 
      lệnh thực thi là các lệnh như phép toán, logic, gọi hàm, quản lý bộ nhớ, điều khiển luồng. 
		  
   + data: vùng nhớ lưu biến toàn cục và các biến static đã được khai báo giá trị. vùng nhớ này có thể đọc/ghi. 
      các biến trong vùng nhớ này tồn tại trong suốt quá trình chạy		  
      	  
   + bss: Vùng nhớ này chuyên lưu trữ các biến toàn cục, các biến static chưa được khai báo giá trị. 
      Các biến trong vùng nhớ này có đặc điểm sẽ được tồn tại trong cả quá trình chương trình chạy và có thể đọc và ghi được.
		  
   + stack: Vùng nhớ này chuyên được cấp phát cho các biến cục bộ trong hàm. 
      Đặc điểm của các biến này là có thể đọc ghi được nhưng sẽ chỉ tồn tại khi hàm còn chạy, khi hàm kết thúc sẽ tự động được giải phóng vùng nhớ.
		  
   + heap: Vùng nhớ Heap được sử dụng để cấp phát bộ nhớ động. Đặc chưng cú pháp khi sử dụng cấp phát động trong ngôn ngữ C là từ khóa calloc, malloc. 
      Đặc điểm của vùng nhớ khi sử dụng cấp phát động là nó sẽ không tự mất đi trong quá trình chạy, và chúng ta phải tự giải phóng vùng nhớ này bằng từ khóa free. 
      Nếu không giải phóng thì vùng nhớ này có thể bị đầy gây ra lỗi.

-Stack: 

 + Nó là một khối bộ nhớ liền kề được phân bổ trong quá trình biên dịch chương trình. 
 + Kích thước của bộ nhớ ngăn xếp bị giới hạn và nó phụ thuộc vào bộ nhớ khả dụng của hệ thống. Kích thước ngăn xếp được xác định trong thời gian biên dịch và không thể tăng lên trong thời gian chạy.
 + Truy cập bộ nhớ từ stack nhanh hơn heap. Điều này là do bộ nhớ stack được tổ chức theo cách liền kề và địa chỉ bộ nhớ được tính toán dễ dàng. 
 + thời gian tồn tại biến trong stack phụ thuộc vào hàm
 + sử dụng để lưu trữ dữ liệu nhỏ và tạm thời và lý tưởng cho các lệnh gọi hàm đệ quy.
 + stack tuân theo nguyên tắc nhập trước xuất trước (LIFO), trong đó giá trị gần đây nhất là giá trị đầu tiên được bật ra.
 
-Heap:

+ không phải là một khối bộ nhớ liền kề và thường lớn hơn stack
+ Kích thước heap không bị giới hạn và có thể phát triển theo yêu cầu. Tuy nhiên, nó có thể bị phân mảnh, có thể dẫn đến rò rỉ bộ nhớ và làm chậm chương trình.
+ Truy cập bộ nhớ từ heap chậm hơn vì nó yêu cầu bảng tra cứu để xác định vị trí bộ nhớ.
+ Biến trong heap có thể tồn tại sau khi hàm trả về 
+ sử dụng để lưu trữ lượng lớn dữ liệu không giới hạn như các cấu trúc dữ liệu động

<font color="GREEN"><b>2. Macro - Function</b></font>

Macro: 
	
  +không có giá trị trả về, không có kiểm tra kiểu dữ liệu đầu vào và không có phạm vi biến
	
  +Macro được thay thế trong preprocessing
	
  +Macro kém hiệu quả hơn về việc sử dụng bộ nhớ và kích thước chương trình
	
  +Nhanh hơn Function bởi không cần trỏ PC tới địa chỉ khác
	
  +Linh hoạt hơn vì không kiểm tra kiểu dữ liệu đầu vào

Function:
	
  +có giá trị trả về, có kiểm tra kiểu dữ liệu đầu vào và có phạm vi biến
	
  +Function được trỏ đến trong khi chạy chương trình
	
  +Khi một hàm được gọi, CPU sẽ đẩy giá trị hiện tại của PC pointer vào trong stack của CPU cùng với các parametter của hàm. TIếp theo chuyển địa chỉ của hàm tới PC pointer và chạy mã trong hàm. Sau khi hàm hoàn thành, CPU khôi phục giá trị trước đó của PC pointer từ stack của CPU và tiếp tục chương trình.
  
<font color="GREEN"><b>3. Static</b></font>
	
  -Từ khoá static để kiểm soát phạm vi và thời gian tồn tại của các biến hoặc hàm
 
 +Biến static: là biến chỉ được khai báo 1 lần trong toàn bộ chương trình, tồn tại trong suốt thời gian chạy chương trình, lưu giữ giá trị của biến ngay cả khi hàm kết thúc.
 
 +Hàm static: chỉ có thể truy cập từ file định nghĩa nó. Không thể truy cập từ các file khác
 
 +Biến toàn cục static: biến chỉ có thể truy cập từ file định nghĩa nó
 
 +Biến cục bộ static: biến chỉ có thể truy cập từ block hoặc hàm định nghĩa nó
 
<font color="GREEN"></font><b>4. Struct - Union</b>

 - Struct:
	
  + Các thành phần trong struct được lưu trữ ở vị trí khác nhau trong bộ nhớ. Địa chỉ luôn là một số chẵn
 	
  + Kích thước của 1 struct lớn hơn hoặc bằng kích thước các thành viên cộng lại tại vì còn phụ thuộc vào bộ nhớ đệm 
 - Onion:
	
  + Các thành phần trong struct được lưu trữ ở cùng địa chỉ trong bộ nhớ
	
  + Union có thể chứa nhiều thành phần nhưng chỉ có thể truy cập 1 thành phần mỗi lần
	
  + Kích thước của union là kích thước của thành phần lớn nhất trong nó
	
  + Việc thay đổi giá trị một thành viên dẫn tới thay đổi giá trị của các thành viên khác
	
  + Điểm mạnh của onion là có thể lưu trữ nhiều kiểu dữ liệu trên cùng một vùng nhớ -> tiết kiệm bộ nhớ.
  
<font color="GREEN"><b>5. Con trỏ</b></font>
 
 - Con trỏ là một biến lưu trữ địa chỉ của một biến hoặc hàm khác.
 
 - Kích thước của con trỏ phụ thuộc vào kiến trúc của vi xử lý. VD: 64-bit -> 8 bytes
 
 - Con trỏ void: trỏ đến mọi địa chỉ (biến int, biến double, hàm, ...). Để truy cập giá trị của biến được con trỏ void trỏ tới ta cần ép kiểu cho con trỏ trước.
 
 - Con trỏ NULL: NULL là một giá trị con trỏ dành riêng đặc biệt không trỏ đến bất kỳ đối tượng dữ liệu hợp lệ nào. Việc cố gắng truy cập vào giá trị con trỏ null trỏ tới sẽ gây lỗi. #define NULL ((void*)0)
 
 - Con trỏ hàm: con trỏ lưu địa chỉ ô nhớ của hàm. Khai báo con trỏ hàm cần khai báo kèm kiểu dữ liệu parameter của hàm. Ứng dụng trở thành một parameter của một hàm khác.
 
 - con trỏ trỏ tới con trỏ: lưu địa chỉ của một con trỏ khác.
 
 Lưu ý: Khi khai báo một con trỏ, nó được xem như là một biến bình thường, tuy nhiên giá trị ban đầu của nó sẽ là một giá trị ngẫu nhiên trong bộ nhớ. Để tránh các lỗi không mong muốn khi truy cập đến vùng nhớ không mong muốn, ta cần phải gán địa chỉ hợp lệ cho con trỏ ngay khi nó được khai báo hoặc khai báo NULL cho nó.
