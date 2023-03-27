#include <lo/lo.h>

int main()
{
  lo_address target = lo_address_new("127.0.0.1", "9000");
  lo_send(target, "testing", "");
  lo_address_free(target);
  return 0;
}
