
int do_nothing(int var_a, char var_b) {
  int x = 0;
  int y;
  y = 10;
  y = y + (int) var_b;
  x = y + 10 + var_a;

  return x;
}

int main() {
  int x = 20;
  int y;

  y = x;
  x = do_nothing(x, 'a');

  return x;
}
