/**
 * A parser program to test the binary search tree implementation
 * @author Duncan
 * @see Bstree
 * <pre>
 * File: BstreeParser.cpp
 * Date: 9999-99-99
 * Course: csc 1254 Section 1
 * Instructor: Dr. Duncan
 * Parses a text file containing statement in the binary search tree
 * "language" that has the following grammar :-
 * delete <item> : removes the specified item from the tree, if in the tree
 * insert <item> : insert the specified item in the tree or overwrite the
 *                 the item with the specified key if it is already in the tree
 * traverse: displays three lists in preorder, inorder, and postorder traversal
 *           of data this tree. one per line.
 * prop: display the following information about this tree
 *        height = ?,  size = ?
 *        ?perfect = ?    ?isomorphic = ?    ?Fibonacci = ?
 * gen <item>:
 * 1. If <item> is not in the tree, "***Geneology***: <item> Non-existent Entry"
 *    is displayed.
 * 2. It the item is in the tree, the following details are displayed:
 *    ***Geneology***: <item>
 *    parent = ? or NONE, left-child = ? or NONE, right-child = ? or NONE
 *    sibling = ? or NONE, sibling's left-child = ? or NONE, sibling's right-child = ? or NONE
 *    #ancestors = ?, #descendants = ?
 *
 * </pre>
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Bstree.cpp"


using namespace std;

/**
 * Displays a string and advances the cursor to the next line
 * @param word the string to be displayed
 */
void printWord(const string& word)
{
    cout << word << endl;
}

int main(int argc, char** argv)
{
    try
    {
        if (argc != 2)
        {
            cerr << "Usage: BstreeParser <Bstree-Prog-Filename>" << endl;
            exit(1);
        }
        string filename = argv[1];
        fstream inFile;
        inFile.open(filename.c_str(), ios::in);
        if (!inFile)
        {
            cerr << "Unable to open " << filename << " for input." << endl;
            exit(2);
        }
        string cmd, token;
        Bstree<string> words;
        while (inFile >> cmd)
        {
            if (cmd == "delete")
            {
                inFile >> token;
                words.remove(token);
                cout << "deleted " << token << endl;
            }
            else if (cmd == "insert")
            {
                inFile >> token;
                words.insert(token);
                cout << "inserted " << token << endl;
            }
            else if (cmd == "traverse")
            {
                cout << endl << "***Traversals***" << endl;
                cout << "======================================" << endl;
                cout << "Preorder Traversal" << endl;
                cout << "--------------------------------------" << endl;
                words.preorderTraverse(printWord);
                cout << "--------------------------------------" << endl;
                cout << "Inorder Traversal" << endl;
                cout << "--------------------------------------" << endl;
                words.inorderTraverse(printWord);
                cout << "--------------------------------------" << endl;
                cout << "Postorder Traversal" << endl;
                cout << "--------------------------------------" << endl;
                words.postorderTraverse(printWord);
                cout << "--------------------------------------" << endl;
                cout << endl;
            }
            else if (cmd == "prop")
            {
                cout << endl << "***Properties***" << endl;
                long treeHeight = words.height();
                long treeSize = words.size();
                string label1 = "?perfect = ", label2 = "?ismorphic = ", label3 = "?Fibonacci = ";
                bool isPerfect = treeSize == static_cast<long>(pow(2, treeHeight + 1)) - 1;
                cout << left << "height = " + to_string(treeHeight)
                    << ", size = " + to_string(treeSize) << endl;
                cout << label1 + (isPerfect ? "true" : "false") << ", "
                    << label2 + (words.isomorphic() ? "true" : "false") << ", "
                    << label3 + (words.isFibonacci() ? "true" : "false") << endl << endl;
            }
            else if (cmd == "gen")
            {
                inFile >> token;
                if (!words.inTree(token))
                    cout << "***Geneology***: " << token << " Non-existent Entry" << endl << endl;
                else
                {
                    cout << endl << "***Geneology***: " << token << endl;
                    const string* par = words.getParent(token);
                    string paren = (par == nullptr ? "NONE" : *par);
                    const string* sib = words.getSibling(token);
                    string sibling = (sib == nullptr ? "NONE" : *sib);
                    const string* lc = words.leftChild(token);
                    string lftChild = (lc == nullptr ? "NONE" : *lc);
                    const string* rc = words.rightChild(token);
                    string rgtChild = (rc == nullptr ? "NONE" : *rc);

                    string label0 = "parent = ", label1 = "sibling = ", label2 = "left-child = ", label3 = " right-child = ",
                        label4 = "sibling = ", label5 = "#ancestors", label6 = "#descendants";
                    cout << label0 + paren + ", "
                        << label1 + sibling + ", "
                        << label2 + lftChild + ", "
                        << label3 + rgtChild << endl;
                    vector<string> ances = words.ancestors(token);
                    cout << label5 << " " << ances.size() << ": ";
                    if (ances.size() > 0)
                    {
                        cout << ances[0];
                        for (int k = 1; k < ances.size(); k++)
                            cout << ", " << ances[k];
                        cout << endl;
                    }
                    else
                        cout << "NONE" << endl;
                    vector<string> desc = words.descendants(token);
                    cout << label6 << " " << desc.size() << ": ";
                    if (desc.size() > 0)
                    {
                        cout << desc[0];
                        for (int k = 1; k < desc.size(); k++)
                            cout << ", " << desc[k];
                        cout << endl;
                    }
                    else
                        cout << "NONE" << endl;
                    cout << endl;
                }
            }
            else
            {
                throw BstreeException(filename + " parsing error");
            }
        }
    }
    catch (const BstreeException& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}

