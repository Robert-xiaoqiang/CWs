function isValidWalk(walk) 
{
  var ret = walk.length == 10;
  if(ret) {
    var nCount = 0;
    var sCount = 0;
    var wCount = 0;
    var eCount = 0;
    //var i;
    for (i in walk) {
      alert(i);
      if(i == String('n')) {
        nCount++;
      } else if(i == String('s')) {
        sCount++;
      } else if(i == String('w')) {
        wCount++;
      } else {
        eCount++;
      }
    }
    ret = nCount == sCount && wCount == eCount;
  }
  return ret;
}