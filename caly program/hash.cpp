AnsiString hash(AnsiString t, char ch)
{
 AnsiString r;
 char magic = random(15);
 r += magic;
 for(int i =1;i<=t.Length();i++)
  {
   r+=char(t[i]+i+t.Length()+2+magic+ch);
  }
 return r;
}
AnsiString dhash(AnsiString t, char ch)
{
 AnsiString r;
  for(int i =2;i<=t.Length();i++)
  {
   r+=char(t[i]-(i-1)-(t.Length()-1)-2-t[1]-ch);
  }
 return r;
}
 