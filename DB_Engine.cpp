#include "DB_Set.h"
#include "DB_Engine.h"
#include "Relation_Ops.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include <iomanip>

bool DB_Engine::exit = true;

Table* DB_Engine::open_relation(string filename)
{
	ifstream fs;
	ofstream ofs;
	fs.open(filename);
	if(!fs.is_open())
	{
		cerr << "File " << filename << " does not exit" << endl;
		return nullptr;
	}
	string tmp, file;
	while(fs)
	{
		if(tmp=="open")
		{
			cerr<< "File " << filename << " is already open" <<endl;
			return nullptr;
		}
		else
		{
			getline(fs, tmp);
			file.append(tmp);
		}
	}

	fs.close();
	
	DB_Set p;
	
	p.input(file);
	
	file.append("\nopen\n");
	
	ofs.open(filename);
	ofs<<file;
	ofs.close();
	
	DB_Engine::set_exit(false);
	return p.get_last();
}
void DB_Engine::close_relation(Table* relation, string filename)
//write to file without word "open" at end of file
{  
  ofstream file;  
  file.open(filename.c_str());
  
  save_template(relation, file);
  
  //save each tuple
  for(int i=0; i<relation->tuples.size(); ++i)
  {
    save_tuple(relation, relation->tuples[i], file);
  }
  
  file<<"EXIT;";
  
  delete relation;  //take closed relation out of memory
}  


void DB_Engine::save_relation(Table* relation, string filename)
//write to file with word "open" at end of file
{
  ofstream file;  
  file.open(filename.c_str());
  
  save_template(relation, file);
  
  //save each tuple
  for(int i=0; i<relation->tuples.size(); ++i)
  {
    save_tuple(relation, relation->tuples[i], file);
  }
  
  file<<"EXIT;\n";
  file<<"open\n"; //tells engine that relation is already open

}

void DB_Engine::exit_interp()
{
  exit = true;
}

void DB_Engine::show(Table relation)
{
	int width;
	int max_length=6;
	vector<Attribute> templ_attributes = relation.get_Template_Tuple().get_Attributes();
	vector<Attribute> current_tuple;
	
	//set width of fields
	for(int i=0; i<templ_attributes.size(); ++i)
	{
		if(templ_attributes[i].is_Varchar())
		{
			if(templ_attributes[i].get_Length()>max_length)
			{
				max_length = templ_attributes[i].get_Length();
			}
		}
	}
	width = max_length;
	
	cout<<"\nRelation: "<< relation.get_Name()<<"\n\n";
	
	//print column headers
	for(int i=0; i<templ_attributes.size(); ++i)
	{
		cout<< setw(width) << templ_attributes[i].get_Name()<<"  ";
	}
	cout<<"\n";
	
	//print separator
	for(int i=0; i<templ_attributes.size(); ++i)
	{
		for(int j=0; j<=max_length+2; ++j)
    {
      cout<<"-";
    }
	}
	cout<<"\n";
	
	//print tuples
	for(int i=0; i<relation.tuples.size(); ++i)
	{
		current_tuple = relation.tuples[i].get_Attributes();
		
		for(int j=0; j<current_tuple.size(); ++j)
		{
			if(current_tuple[j].is_Varchar())
			{
				cout<<setw(width)<<current_tuple[j].get_String_Value()<<"  ";
			}
			else
			{
				cout<<setw(width)<<current_tuple[j].get_Int_Value()<<"  ";
			}
		}
		cout<<"\n";
	}	
}

Table* DB_Engine::create_relation(string name, Tuple tuple_template)
{
  Table* relation = new Table(name, tuple_template);
  return relation;
}

void DB_Engine::update(Table* relation, vector<string> attribute_names, vector<string> values, Condition cond)
{
	Table update_list = *Relation_Ops::select(cond, *relation);		//table of tuples to be updated
	vector<Tuple> tuples = update_list.tuples;						//list of tuples to be updated
	
	//check to make sure number of update values matches number of attributes to be updated
	if(values.size()!=values.size())
	{
		cerr<<"Different number of attribtues and values in update func";
	}
	
	//replace necessary attributes
	for(int i=0; i<relation->tuples.size(); ++i)
	{
		for(int j=0; j<tuples.size(); ++j)
		{
			if(relation->tuples[i]==tuples[j])
			{
				for(int k=0; k<values.size(); ++k)
				{
       
          relation->tuples[i].replace_Attribute(attribute_names[k], values[k]);
          
				}
			}
		}
	}
	
	
}

void DB_Engine::insert_tuple(Table* relation, Tuple tuple)
{
	relation->insert(tuple);
}

void DB_Engine::insert_relation(Table* relation, Table new_relation)
{
	/*NEED TO CHECK UNION COMPATIBLE HERE*/
	
	//insert each tuple of new_relation into relation
	for(int i=0; i<new_relation.tuples.size(); ++i)
	{
		relation->insert(new_relation.tuples[i]);
	}
}

void DB_Engine::remove_query(Table* relation, Condition cond)
{
	Table update_list = *Relation_Ops::select(cond, *relation);		//table of tuples to be updated
	vector<Tuple> tuples = update_list.tuples;						//list of tuples to be updated
	
	//remove each tuple in tuples from relation
	for(int i=0; i<tuples.size(); ++i)
	{
		relation->remove(tuples[i]);
	}
}

/***********************************************************************************
Helper functions
************************************************************************************/

void DB_Engine::save_template(Table* relation, ofstream& file)
{
  vector<Attribute> primary_key;
  vector<Tuple> tuples = relation->tuples;
  vector<Attribute> tuple_template = relation->get_Template_Tuple().get_Attributes();
  
  
  file<<"CREATE TABLE " << relation->get_Name() << " (";
  
  //print list of Attributes
  for(int i=0; i<tuple_template.size(); ++i)
  {
    if(i!=0)
    {
      file<<", ";
    }
    
    if(tuple_template[i].is_Primary())
    {
      primary_key.push_back(tuple_template[i]);
    }
    file<< tuple_template[i].get_Name() << " ";

    if(tuple_template[i].is_Int())
    {
      file<< "INTEGER";
    }
    else if(tuple_template[i].is_Varchar())
    {
      file<< "VARCHAR(" << tuple_template[i].get_Length() << ")";
    }
    else
    {
      cerr<<"no valid attribute type";
    }
  }  
    
  file<<") PRIMARY KEY (";
  
  //print list of primary keys
  if(primary_key.size() == 0)
  {
    cerr<<"No primary keys";
  }
  else
  {
    for(int i=0; i<primary_key.size(); ++i)
    {
      if(i!=0)
      {
        file<<", ";
      }
      file<< primary_key[i].get_Name();
    }
    file<<");\n";
  }   
}

void DB_Engine::save_tuple(Table* relation, Tuple tuple, ofstream& file)
{
  vector<Attribute> attributes = tuple.get_Attributes();
  
  file<<"INSERT INTO "<< relation->get_Name() << " VALUES FROM (";
  
  //print list of attribute values
  for(int i=0; i<attributes.size(); ++i)
  {
    if(i!=0)
    {
      file<<", ";
    }
    
    if(attributes[i].is_Varchar())
    {
      file<<"\""<<attributes[i].get_String_Value()<<"\"";
    }
    else
    {
      file<<attributes[i].get_Int_Value();
    }
  }
  file<<");\n";
} 