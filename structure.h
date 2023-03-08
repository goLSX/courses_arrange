#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED



#define MaxClass  100		//课程总数不超过100
#define MaxTerm   12		//学期总数不超过12
#define MaxCredit 30            //每学期学分不超过30


//   邻接表表示
typedef struct AdjVexNode {
	int AdjVex;			//邻接点位序
	AdjVexNode * Next;		//指向下一个邻接点的指针
}AdjVexNode;				//邻接表结点


typedef struct  {			//顶点表结点
	char data[3];			//课程编号
	int credit;			//节点学分（每门课学分）
	AdjVexNode* FirstArc;		//指向邻接表第一个邻边节点的指针域
	int In_degree;			//课程入度
}VexNode;				//图节点

typedef struct  {
	int term_num;			//学期数
	int max_credit;			//每学期学分上限
}Message;				//学期信息

typedef struct  {			//图
	VexNode* Vex;			//邻接表域
	int VexNum;			//节点数
	int ArcNum;			//边数
	Message* mes;			//每学期的信息(允许修改)
}Class_arrange_Graph;
#endif // STRUCTURE_H_INCLUDED
