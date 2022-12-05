# CtrlZTree
To have an history of modification in the form of a tree instead of a stack wich lead in no loss of data in the short term (First idea is for a vscode plugin)
(Basically it's git but working on RAM and with automatic commits when doing modifications and branching before commit if modifications after doing a ctrl-z... yes I could probably modify git's algorithm instead but..)

First we will be creating an api (receiving commands by a pipe) coded in c that will be storing the state and can return parts of the tree.

## Data structure / Definitions

tree : (node id : sha256 hash of data, also called head or hash)
data : (diff between parent node and actual node)

head will refer to the hash of the actual node id (referencing the position on the tree)

## Commands
`set <raw data>` : compute the sha256 hash as head and compute diff from parent node as data (data will be continuing the current branch of the tree but if the hash already exist on the tree, head will be moved to the position of the hash) and return the new head value

`head [hash]` : if hash provided will set the head to the position of the hash, else it will return the hash of the head

`z` : will move head to the parent node if exist

`y` : will move to the children if only one exist, else will return the list of childrens (heads)

`get [hash]` : will return the data (diff) at the hash (if no hash provided, use head as hash)

`rget [hash]` : will return the raw data (actual state of the document by applying all modifications from root to the given hash/node id/head if no hash provided)
