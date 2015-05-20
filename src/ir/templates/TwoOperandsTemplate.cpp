#include <tuple>
#include <stdexcept>

#include "AnalysisProcessor.h"
#include "Inst.h"
#include "TwoOperandsTemplate.h"


void TwoOperandsTemplate::templateMethod(
    AnalysisProcessor &ap,
    Inst &inst,
    const std::vector< std::tuple<IRBuilderOperand::operand_t, uint64_t, uint32_t, uint64_t, uint64_t, uint64_t, uint64_t> > &operands,
    std::string insName) const
{
  if (operands.size() < 2) // TODO, MOV = 2, ADD = 3, virer le < et mettre un template 3op
    throw std::runtime_error("Wrong numbers of operands: "
                           + insName
                           + " instruction must have two operands.");

  // reg, imm
  if (std::get<0>(operands[0]) == IRBuilderOperand::REG &&
      std::get<0>(operands[1]) == IRBuilderOperand::IMM)
    this->regImm(ap, inst);

  // reg, reg
  if (std::get<0>(operands[0]) == IRBuilderOperand::REG &&
      std::get<0>(operands[1]) == IRBuilderOperand::REG)
    this->regReg(ap, inst);

  // reg, mem
  if (std::get<0>(operands[0]) == IRBuilderOperand::REG &&
      (IRBuilder::isMemOperand(std::get<0>(operands[1])) || std::get<0>(operands[1]) == IRBuilderOperand::LEA))
    this->regMem(ap, inst);

  // mem, imm
  if (IRBuilder::isMemOperand(std::get<0>(operands[0])) &&
      std::get<0>(operands[1]) == IRBuilderOperand::IMM)
    this->memImm(ap, inst);

  // mem, reg
  if (IRBuilder::isMemOperand(std::get<0>(operands[0])) &&
      std::get<0>(operands[1]) == IRBuilderOperand::REG)
    this->memReg(ap, inst);
}

