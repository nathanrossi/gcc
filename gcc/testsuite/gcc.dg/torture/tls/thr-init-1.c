/* { dg-do run } */
/* { dg-require-effective-target tls_runtime } */
/* { dg-add-options tls } */
/* { dg-skip-if "TLS local exec code cannot be linked into shared objects" { alpha*-*-linux* } { "-pie" } { "" } } */

extern int printf (char *,...);
extern void abort() ;

int test_code(int b)
{
static __thread int fstat = 1;
  fstat += b ;
  return fstat;
}

int main (int ac, char *av[])
{
  int a = test_code(1);
  
  if ( a != 2 )
    {
      printf ("a=%d\n", a) ;
      abort ();
    }
  
  return 0;
}
