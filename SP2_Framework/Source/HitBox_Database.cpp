#include "HitBox_Database.h"

CHitBox_Database::CHitBox_Database(void)
{
    head = tail = current = newNode = prev = 0;
}

CHitBox_Database::~CHitBox_Database(void)
{

}

void CHitBox_Database::Insert(CCollision_HitBox newData)
{
    newNode = new CCollision_Node(newData);
    
    if (head == NULL)
    {
        head = tail = newNode;
    }

    else
    {
        //Insert the new integer to the tail
        newNode->back = tail;
        tail->next = newNode;   //Linked 
        tail = newNode;         //tail is the latest node
    }
}

bool CHitBox_Database::Delete(CCollision_HitBox newData)
{
    if (head != NULL) 
	{
        current = head;

        while (current != NULL)
        {
            if (newData.max[0] == current->data.max[0] && 
                newData.max[1] == current->data.max[1] &&
                newData.max[2] == current->data.max[2] &&
                newData.min[0] == current->data.min[0] &&
                newData.min[1] == current->data.min[1] &&
                newData.min[2] == current->data.min[2])
            {
                break;
            }

            else
            {
                prev = current;
                current = current->next;
            }
        }


        //analyse the current ptr
        if (current == head)
        {
            // the data to be deleted is in 1st node
            if (head->next != NULL)
            {
                //there are more than 1 node in the LL
                head = head->next;
                head->back = NULL;
                delete current;
                return true;
            }
            else
            {
                //only one node in the LL
                delete current;
                head = tail = NULL;
                return true;
            }
        }
        else if (current == tail)
        {
            // data to be deleted is in the last node
            tail = prev;
            tail->next = NULL;
            delete current;
            return true;
        }
        else if (current == NULL)
        {
            // no such data found in the LL
            return false;
        }
        else
        {
            // data to be deleted is somewhere in the middle
            prev->next = current->next;
            current->next->back = prev;
            delete current;
            return true;
        }
    }
    else
        return false;
}