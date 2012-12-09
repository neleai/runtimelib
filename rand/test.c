int main(){ long i;
  int r;
  initstate(0);
  for(i=0;i<1000000000;i++){
    r+=random();
  }
  return r;
}
