/** @file
 *****************************************************************************

 Declaration of interfaces for a verfication program provided by server requester

 *****************************************************************************
 * @author     This file is part of libserver, developed by alittlehorse
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef OSPREY_proof_program_H
#define OSPREY_proof_program_H





namespace libserver{
    class proof_program{
        private:
        std::string assembly_fn;
        std::string processed_assembly_fn;
        std::string architecture_params_fn;
        std::string computation_bounds_fn;
        std::string primary_input_fn;
        std::string auxiliary_input_fn;
        std::string _program_name;
        void processe_program(){
            assembly_fn = _program_name +"/"+ _program_name+".s";
            processed_assembly_fn = _program_name +"/"+ _program_name+"-processed_assembly";
            architecture_params_fn = _program_name +"/"+ _program_name+"-architecture_params.txt";
            primary_input_fn = _program_name +"/"+ _program_name+"-primary_input.txt";
            auxiliary_input_fn = _program_name +"/"+ _program_name+"-auxiliary_input.txt";
            computation_bounds_fn = _program_name +"/"+ _program_name+"-computation_bounds.txt";
        };
        public:
        std::string get_assembly_fn();
        std::string get_processed_assembly_fn();
        std::string get_architecture_params_fn();
        std::string get_computation_bounds_fn();
        std::string get_primary_input_fn();
        std::string get_auxiliary_input_fn();
        std::string get_program_name();
        proof_program() = default;
        explicit proof_program(std::string program_name);



    };
}
#endif //OSPREY_proof_program_H