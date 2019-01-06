var size = 10;//size为最小不可再分阈值

var MAX = 1024;//内存大小为1024K
var flag = 0;//标记

//freeTable[0][0] = new Array(3,0,100,1);


// // 二维
// var freeTable = new Array();
// freeTable[0] = new Array(3,0,100,1);
// freeTable[1] = new Array(1,100,2,1);



// 三维
var freeTable = new Array();
freeTable[0] = new Array();
freeTable[0][0] = new Array(1,0,200,1);
freeTable[0][1] = new Array(2,200,10,0);
freeTable[0][2] = new Array(3,210,90,1);
freeTable[0][3] = new Array(4,300,100,1);
freeTable[0][4] = new Array(5,400,60,1);
freeTable[0][5] = new Array(6,460,770,0);
// freeTable[0][0] = new Array('free',0,MAX,0);

freeTable[1] = new Array();
freeTable[1][0] = new Array(1,0,200,1);
freeTable[1][1] = new Array(2,200,10,0);
freeTable[1][2] = new Array(3,210,90,1);
freeTable[1][3] = new Array(4,300,100,1);
freeTable[1][4] = new Array(5,400,60,1);
freeTable[1][5] = new Array(6,460,770,0);
// freeTable[1][0] = new Array('free',0,MAX,0);

freeTable[2] = new Array();
freeTable[2][0] = new Array(1,0,200,1);
freeTable[2][1] = new Array(2,200,10,0);
freeTable[2][2] = new Array(3,210,90,1);
freeTable[2][3] = new Array(4,300,100,1);
freeTable[2][4] = new Array(5,400,60,1);
freeTable[2][5] = new Array(6,460,770,0);

// freeTable[2][0] = new Array('free',0,MAX,0);

freeTable[3] = new Array();
freeTable[3][0] = new Array(1,0,200,1);
freeTable[3][1] = new Array(2,200,10,0);
freeTable[3][2] = new Array(3,210,90,1);
freeTable[3][3] = new Array(4,300,100,1);
freeTable[3][4] = new Array(5,400,60,1);
freeTable[3][5] = new Array(6,460,770,0);

// freeTable[3][0] = new Array('free',0,MAX,0);

function recycle()
{
	var value = document.getElementById("text").value;//要回收的分区号
	if(value == '')
	{
		alert('请输入正确的数据!');
		return false;
	}
	for(var num = 0;num<4;num++){
		for(var i = 0;i< freeTable[num].length;i++)
		{//0分区号 1起始地址 2大小 3状态

			if (freeTable[num][i][3] &&freeTable[num][i][0] == value )
			{
				if(i==0)
				{
					if(freeTable[num][i+1][3])
					{
						freeTable[num][i][3] = 0;
						//alert('12');
						break;
					}
					else
					{
						freeTable[num][i][2] +=  freeTable[num][i+1][2];
						freeTable[num][i][3] = 0;
						freeTable[num].splice(i+1,1);//删除i
						//alert('22');
						break;
					}
				}

			    if(i == freeTable[num].length -1 )//最后
				{
					if(!freeTable[num][i-1][3])//且倒数第二空闲
					{
						freeTable[num][i-1][2] = freeTable[num][i-1][2] + freeTable[num][i][2];
						freeTable[num].splice(i,1);//删除i
						
						//alert('42');
						break;	
					}
					else
					{
						freeTable[num][i][3] = 0;
						//alert('32');
						
						break;				
					}
				}
				

				if(!freeTable[num][i-1][3] && !freeTable[num][i+1][3])//前后均空闲
				{
					freeTable[num][i-1][2] = freeTable[num][i-1][2] + freeTable[num][i][2]+freeTable[num][i+1][2];
					//alert('52');
					freeTable[num].splice(i,1);//删除i
					freeTable[num].splice(i,1);//删除i+1
					//freeTable[num].splice(i+2,1);//删除i+1
					break;
				}
			    else if (!freeTable[num][i-1][3]){//前空闲
			    	//alert('62');
					freeTable[num][i-1][2] = freeTable[num][i-1][2] + freeTable[num][i][2];
					freeTable[num].splice(i,1);//删除i
					break;
				}
				 else if (!freeTable[num][i+1][3]) {//后空闲
					freeTable[num][i][2] = freeTable[num][i][2] +  freeTable[num][i+1][2];
					freeTable[num][i][3] = 0;
					//alert('72');
					freeTable[num].splice(i+1,1); //删除i+1
					break;
				}
				else{//前后均占用, 加一条记录
					//alert('82');
					freeTable[num][i][3] = 0;
					break;
				}
			}

	
		}
	}
	onload();

}

//计算剩余空间
function leftMemory(num)
{
	var length =  freeTable[num].length;
	var free  = MAX;
 	for (var i = 0; i < freeTable[num].length; i++){
		free = free - freeTable[num][i][2];
	}
 	return free;
}



function firstFit(id,request)//首次适应
{
	var num =0;
	for(var i = 0; i < freeTable[num].length ; i++ )
		{
			if(!freeTable[num][i][3] && request<freeTable[num][i][2])
				{
					if(freeTable[num][i][2] - request > size)//从i分区画出request大小的空间
					{
						freeTable[num][i][2] = freeTable[num][i][2]- request ;//修改分区大小
						newrow = new Array(id,freeTable[num][i][1]+freeTable[num][i][2],request,1);
						freeTable[num].splice(i+1,0,newrow);
						return true;
					}
					else
						{
							freeTable[num][i][0] = id;//修改分区号
							freeTable[num][i][3] = 1;//修改状态为已分配
							return true;
						}
				}
		}
		alert("首次适应算法内存空间不足，无法分配!");
		return false;
}




function netxFit(id,request)//循环首次
{
	var num = 1;
	if(flag==-1)//表示第一次，flag无标记,从头开始扫描
		flag = 0;
	for(var i = flag; i < freeTable[num].length ; i++ )
		{
			if(request <freeTable[num][i][2] && !freeTable[num][i][3])
				{
					if(freeTable[num][i][2] - request > size)//从i分区画出request大小的空间
					{
					 	flag = i+1;
						freeTable[num][i][2] = freeTable[num][i][2]- request ;//修改分区大小
						newrow = new Array(id,freeTable[num][i][1]+freeTable[num][i][2],request,1);
						freeTable[num].splice(i+1,0,newrow);
						return true;
					}
					else{
					 	flag = i+1;
						freeTable[num][i][0] = id;//修改分区号
						freeTable[num][i][3] = 1;//修改状态为已分配
						return true;
					}
				}
		}

	for(var i = 0; i < flag ; i++ )
		{
			if(request <freeTable[num][i][2] && !freeTable[num][i][3])
				{
					if(freeTable[num][i][2] - request > size)//从i分区画出request大小的空间
					{
					 	flag = i+1;
						freeTable[num][i][2] = freeTable[num][i][2]- request ;//修改分区大小
						newrow = new Array(id,freeTable[num][i][1]+freeTable[num][i][2],request,1);
						freeTable[num].splice(i+1,0,newrow);
						return true;
					}
					else{
					 	flag = i+1;
						freeTable[num][i][0] = id;//修改分区号
						freeTable[num][i][3] = 1;//修改状态为已分配
						return true;
					}
				}
		}
 	

	alert("循环适应算法内存空间不足，无法分配!");
	return false;

}

function bestFit(id,request)//差值最小
{
	var num = 2;
	
	var Min = 1024;//记录差值最小
	var j = -1;//记录差值最小的分区位置
	for(var i = 0; i < freeTable[num].length ; i++ )
	{
		if( !freeTable[num][i][3] && freeTable[num][i][2] > request)//空闲且空间足够大
			{
				if(freeTable[num][i][2] - request < Min)
					{
						Min = freeTable[num][i][2] - request;
						j = i;//更新j
					}
			}
	}


	if(freeTable[num][j][2]-request > size)//从j分区画出request大小的空间
		{
			freeTable[num][j][2] = freeTable[num][j][2]- request ;//修改分区大小
			newrow = new Array(id,freeTable[num][j][1]+freeTable[num][j][2],request,1);
			freeTable[num].splice(j+1,0,newrow);
			//show();
			return true;
		}
	else
		{
			//alert(freeTable3[j][0]);
			freeTable[num][j][0] = id;//修改分区号
			freeTable[num][j][3] = 1;//修改状态为已分配
			//show();
			return true;
		}
	
	alert("最佳适应算法内存空间不足，无法分配!");
	return false;

}


function worstFit(id,request)//最坏匹配
{
	var num =3;
	var Max = 0;//记录差值最大
	var j = -1;
	//选择法找出最大的分区号
	for(var i = 0; i < freeTable[num].length ; i++ )
		{
			if( !freeTable[num][i][3] && freeTable[num][i][2] > request)//空闲且空间足够大
				{
					if(freeTable[num][i][2] - request > Max)
						{
							Max = freeTable[num][i][2] - request;
							j = i;//更新j
						}
				}
		}


	if(freeTable[num][j][2] - request > size)//从i分区画出request大小的空间
	{
		freeTable[num][j][2] = freeTable[num][j][2]- request ;//修改分区大小
		newrow = new Array(id,freeTable[num][j][1]+freeTable[num][j][2],request,1);
		freeTable[num].splice(j+1,0,newrow);
		//show();
		return true;
	}
	else
		{
			//alert(freeTable4[j][0]);
			freeTable[num][j][0] = id;//修改分区号
			freeTable[num][j][3] = 1;//修改状态为已分配
			//show();
			return true;
		}


	alert("最坏适应算法内存空间不足，无法分配!");
	return false;
}




//生成表格数据
function content(num)
{
	
	var head ="";
	head += "<table cellspacing='0px' padding='0px'   border='1px'><tr><td nowrap='nowrap'>\
		分区号</td><td nowrap='nowrap'>分区始址</td><td nowrap='nowrap' >大小</td><td nowrap='nowrap'>状态</td></tr>";
	var body="";
	//alert(freeTable[num][1][2]);
	for(var i=0;i<freeTable[num].length;i++)
	{
		body +="<tr>";
		for(var j=0;j<freeTable[num][i].length-1;j++)
		{
				body +="<td>" + freeTable[num][i][j];
				
		}
		body +="K</td><td>"+(freeTable[num][i][3]==1?"占用":"空闲")+"</td></tr>";
	}

	body +="</table>";

	return head+body;
}


//生成图的数据
var a=0;
function show(num)
{
	//var num =0;
    var head ="";
    var body="";
    var height = 500;
    head+="<table id='Table' style='border:2px solid;height:"+height+'px;\'>';
	console.log(freeTable[num].length);
	console.log(freeTable[num][0][0]);

    for(var i=0;i<freeTable[num].length;i++)
    {
    	 body+="<tr>";
	     if(!freeTable[num][i][3])//表示空闲
	         body+="<td id='Table' style='height:"+freeTable[num][i][2]/1024*height+"px;\'>"+freeTable[num][i][2]+"K</td></tr>";
        else
             body+="<td  id='Table' class='busy' style='height:"+freeTable[num][i][2]/1024*height+"px;\'>"+freeTable[num][i][2]+"K</td></tr>";
    }


    var oUl = document.getElementById("ul"+num+num);
    oUl.removeChild(document.getElementsByTagName("li")[a++]);
   
    var OLi = document.createElement("li");
   	OLi.innerHTML = content(num);
   	console.log(OLi.innerHTML);
   	oUl.appendChild(OLi);
    
   	var oUl2 = document.getElementById("ul"+num+(num+1));
    oUl2.removeChild(document.getElementsByTagName("li")[a++]);
    var OLi1 = document.createElement("li");
   	OLi1.innerHTML = head+body;
   	oUl2.appendChild(OLi1);
   	if(a>7)
   		a  = 0;

}

function onload()
{
	for(var i = 0;i<4;i++)
		show(i);
}

function main()
{
	var value = document.getElementById("text").value;
	var id = value.split(',')[0],request = value.split(',')[1];
	if(value==''|| !request)//捕捉异常，不输入数据时点击分配按钮给出提示
	{
		alert('请输入正确的数据!');
		return false;
	}

	firstFit(id,request);
	netxFit(id,request);
	bestFit(id,request);
	worstFit(id,request);
	onload();


}