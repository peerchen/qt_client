#include "QuoteStandardItemModel.h"

#include "Macrodefs.h"
#include <QThread>

QuoteStandardItemModel::QuoteStandardItemModel(QObject *parent)    : QStandardItemModel(parent)
{
	m_nStartSel   = 0;
    m_cDecimal    = NULL;

	//只是初始化，有函数进行设置
    m_upColor     = QColor("#ff786e");
    m_downColor   = QColor("#6cad3c");
    m_noneColor   = QColor("#e8e8e8");
    m_normalColor = QColor("#e8e8e8");

	connect(this, &QuoteStandardItemModel::recover, this, &QuoteStandardItemModel::recoverSlot);
	//InitData();
}

//表格改变时触发，如增加，删除row
//dataChanged时触发
//有数据update时触发
QVariant QuoteStandardItemModel::data(const QModelIndex & index, int role) const
{
	QString strTmp;
	
    int column = index.column();
    int row    = index.row();

    if (role == Qt::DisplayRole)//视图的文本显示
    {
        //20180305  屏蔽一个BUG
        if (  m_vecData.size()  <= 0)
              return  QVariant();
   
        return  m_vecData[row].arrVar[column];
    }
	if (Qt::TextAlignmentRole == role)//文本对齐
	{
		return (int)(Qt::AlignCenter);
	}

	//恢复原来的颜色
    if (Qt::TextColorRole == role)//设置显示的颜色,和 ForegroundRole 一样
    {
		return  QColor("#dab96b");

        switch (column)
		{
		case 0:
		case 1:
			return  QColor("#dab96b");
		case 3:
		case 4:
		case 5:
		case 6:
		case 8:
		{
			if (row > m_vecData.size() - 1 || m_vecData.size() < 1)
				return m_noneColor;

			//GcnTableRow table = m_vecData[row];
			if (m_vecData[row].arrColor[column] == 1)
			{
				return m_upColor;
			}
			else if (m_vecData[row].arrColor[column] == -1)
			{
				return m_downColor;
			}
			else
				return QColor("#dab96b");//m_noneColor
		}
		default:
			return  QColor("#dab96b");//m_noneColor
        }
    }
    return QStandardItemModel::data(index, role);
}


bool QuoteStandardItemModel::recoverSlot(int row, int column)
{
	//QThread::msleep(20);
	m_vecData[row].arrColor[column] = 0;

	//item(row, column)->setBackground(QBrush(QColor("#181a1d")));

	emit dataChanged(createIndex(row, column), createIndex(row, column));

	return  true;
}

void QuoteStandardItemModel::recoverAllBackground()
{
	for (auto i=0; i< m_vecData.size();  ++i)
	{
		for (auto j = 0; j < 23; ++j)
		{
			item(i, j)->setBackground(QBrush(QColor("#181a1d")));
		}
	}
}
//表头单元格，文字靠右对齐
QVariant QuoteStandardItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::TextAlignmentRole && orientation == Qt::Horizontal)
      {
          //return int(Qt::AlignLeft | Qt::AlignVCenter);
		   return int(Qt::AlignCenter);
      }
    return QStandardItemModel::headerData(section,orientation,role);
}


bool QuoteStandardItemModel::setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */)
{
    if(index.row() < 0 || index.column() < 0)
        return false;

	if (Qt::TextColorRole == role)
	{
		m_vecData[index.row()].arrColor[index.column()] = value.toInt();
		return  true;
	}

    m_vecData[index.row()].arrVar[index.column()] = value;
    return true;
}

//初始化使用
bool QuoteStandardItemModel::InitItem(const int &row, const int  &column,const QVariant& value)
{
	if (row < 0 || column < 0)
		return false;

	if (m_vecData.size() <= row)
	{
		GcnTableRow tablrow;	
		tablrow.arrVar[column]   = value;
		tablrow.arrColor[column] = 0;
		m_vecData.push_back(tablrow);
	}
	else
	{
		m_vecData[row].arrVar[column] = value;
		
	}

	return true;
}

//更新数据使用
bool QuoteStandardItemModel::updateItem(const int &row, const int  &column, const QVariant& value)
{
	if (row < 0 || column < 0)
		return false;

	if (m_vecData.size() <= row)
	{
		GcnTableRow tablrow;
		tablrow.arrVar[column] = value;
		m_vecData.push_back(tablrow);
	}
	else
	{
		QString oldval = m_vecData[row].arrVar[column].toString();
		
		//变色
		if (column != 0 && column != 1 & column != 2)
		{
			int type = 0;
			if (column == 3 || column == 4|| column == 5 || column == 6 || column == 8)
			{
				QString newPrice = m_vecData[row].arrVar[3].toString();
				QString prePrice = m_vecData[row].arrVar[11].toString();
				if (newPrice.toDouble() * 100 >= prePrice.toDouble() * 100)
				{
					m_vecData[row].arrColor[column] = 1;
					type = 1;
				}
				else
				{
					m_vecData[row].arrColor[column] = -1;
					type = 0;
				}

			}

			else
			{
				if (oldval.toDouble() > value.toDouble())
				{
					m_vecData[row].arrColor[column] = -1;
					type = 0;
				}
				else
				{
					m_vecData[row].arrColor[column] = 1;
					type = 1;
				}
			}
			//先变一次色
			QStandardItem *pItem = item(row, column);
			if (pItem)
			{
				if (type >= 1)
					item(row, column)->setBackground(QBrush(m_upColor));
				else
					item(row, column)->setBackground(QBrush(m_downColor));
				//test
				
			}
			//updateItem(row, column, m_vecData[row].arrColor[column]);
		}

		m_vecData[row].arrVar[column] = value;	
		//触发数据变颜色
		emit dataChanged(createIndex(row, column), createIndex(row, column));

		//QThread::msleep(20);
		//触发恢复颜色
		//emit recover(row, column);
	}


	return true;
}

// 初始化值
void QuoteStandardItemModel::InitData()
{
    QFile file(_RES_DATADB_PATH + _MY_TEXT("grades.txt"));

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream stream(&file);
        QString line = stream.readLine();
        QStringList list = line.split(",", QString::SkipEmptyParts);

        int row = 0;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            if (!line.startsWith("#") && line.contains(","))
            {
                list= line.split(",");
				
				GcnTableRow tablrow;
                for (int col = 0; col < list.length(); ++col)
                {
					tablrow.arrVar[col] = list.at(col);
					//if (col == 4 || col == 5)
					if (col >= 3 && col <= 15)
					{
						tablrow.arrVar[col] = "--";
						if (tablrow.arrVar[col] >= 0)
						{
							tablrow.arrColor[col] = 1;//值大于0，显示红色
						}
						else
						{
							tablrow.arrColor[col] = -1;
						}
					}
                }
                
				m_vecData.push_back(tablrow);

            }
        }
    }
    file.close();
}

void QuoteStandardItemModel::ClearAllData()
{
	m_vecData.clear();
}

void QuoteStandardItemModel::setVerticalHeaderLabels(const QStringList &labels)
{
	return QStandardItemModel::setVerticalHeaderLabels(labels);
}

