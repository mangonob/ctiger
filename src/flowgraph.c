#include "flowgraph.h"

AS_instr FG_instr(G_node n)
{
  return (AS_instr)G_nodeInfo(n);
}

Temp_tempList FG_def(G_node n)
{
  AS_instr instr = FG_instr(n);

  switch (instr->kind)
  {
  case I_OPER:
    return instr->OPER.dst;
  case I_MOVE:
    return instr->MOVE.dst;
  case I_CALL:
    return instr->CALL.oper->OPER.dst;
  case I_LABEL:
    return NULL;
  }
}

Temp_tempList FG_use(G_node n)
{
  AS_instr instr = FG_instr(n);

  switch (instr->kind)
  {
  case I_OPER:
    return instr->OPER.src;
  case I_MOVE:
    return instr->MOVE.src;
  case I_CALL:
    return instr->CALL.oper->OPER.src;
  case I_LABEL:
    return NULL;
  }
}

AS_targets FG_targets(G_node n)
{
  AS_instr instr = FG_instr(n);

  switch (instr->kind)
  {
  case I_OPER:
    return instr->OPER.jumps;
  case I_CALL:
    return instr->CALL.oper->OPER.jumps;
  default:
    return NULL;
  }
}

bool FG_isMove(G_node n)
{
  return FG_instr(n)->kind == I_MOVE;
}

static G_node FG_findNodeByInstr(G_nodeList nl, AS_instr instr)
{
  if (nl && instr)
  {
    for (; nl; nl = nl->tail)
      if (G_nodeInfo(nl->head) == instr)
        return nl->head;
  }
  return NULL;
}

void FG_show(FILE *out, G_graph graph, AS_instrList il, Temp_map m)
{
  G_nodeList nList = G_nodes(graph);

  for (; il; il = il->tail)
  {
    AS_instr instr = il->head;
    switch (instr->kind)
    {
    case I_LABEL:
      AS_print(out, instr, m);
      break;
    default:
    {
      G_node node = FG_findNodeByInstr(nList, instr);
      int i = G_nodeListFindIndex(nList, node);
      if (node && i >= 0)
      {
        fprintf(out, "    %d.\t", i + 1);
        AS_print(out, instr, m);
        G_nodeList succs = G_succ(node);
        if (succs)
        {
          fprintf(out, "\t==> { ");
          for (; succs; succs = succs->tail)
          {
            int found = G_nodeListFindIndex(nList, succs->head);
            if (found >= 0)
              fprintf(out, "%d", found + 1);

            if (succs->tail)
              fprintf(out, ", ");
          }
          fprintf(out, " }");
        }
      }
      break;
    }
    }

    fprintf(out, "\n");
  }
}

G_graph FG_AssemFlowGraph(AS_instrList il)
{
  G_graph graph = G_Graph();

  TAB_table nodes = TAB_empty();
  for (AS_instrList iList = il; iList; iList = iList->tail)
  {
    AS_instr instr = iList->head;
    if (instr->kind != I_LABEL)
      TAB_push(nodes, instr, G_Node(graph, instr));
  }

  // key: Label of a label instructions
  // value: First nonlabel instructions after the label instructions
  TAB_table labeled_node = TAB_empty();
  Temp_labelList lab_block = NULL;
  for (AS_instrList iList = il; iList; iList = iList->tail)
  {
    AS_instr instr = iList->head;
    if (instr->kind == I_LABEL)
    {
      lab_block = Temp_LabelList(instr->LABEL.label, lab_block);
    }
    else if (lab_block != NULL)
    {
      for (; lab_block; lab_block = lab_block->tail)
        TAB_push(labeled_node, lab_block->head, TAB_lookup(nodes, instr));
    }
  }

  G_node prev = NULL;
  for (AS_instrList iList = il; iList; iList = iList->tail)
  {
    AS_instr instr = iList->head;
    // Skip label instructions
    if (instr->kind == I_LABEL)
      continue;

    G_node node = TAB_lookup(nodes, instr);
    if (prev)
      G_addEdge(prev, node);

    AS_targets targets = FG_targets(node);
    for (Temp_labelList labs = targets ? targets->labels : NULL; labs; labs = labs->tail)
    {
      G_node to = TAB_lookup(labeled_node, labs->head);
      if (to)
        G_addEdge(node, to);
    }

    if (AS_isBranch(instr))
      prev = NULL;
    else
      prev = node;
  }
  return graph;
}
