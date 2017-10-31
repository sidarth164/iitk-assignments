package in.ac.iitk.cse.cs252.transactions;

import org.bitcoinj.core.ECKey;
import org.bitcoinj.core.NetworkParameters;
import org.bitcoinj.core.Transaction;
import org.bitcoinj.core.Utils;
import org.bitcoinj.crypto.DeterministicKey;
import org.bitcoinj.crypto.TransactionSignature;
import org.bitcoinj.script.Script;
import org.bitcoinj.script.ScriptBuilder;

import java.io.File;
import java.math.BigInteger;

import static org.bitcoinj.script.ScriptOpCodes.*;

/**
 * Created by bbuenz on 24.09.15.
 */
public class MultiSigTransaction extends ScriptTransaction {
    // TODO: Problem 3
    private ECKey bank_key;
    private ECKey customer_1_key;
    private ECKey customer_2_key;
    private ECKey customer_3_key;

    public MultiSigTransaction(NetworkParameters parameters, File file, String password) {
        super(parameters, file, password);
        bank_key = randKey();
        customer_1_key = randKey();
        customer_2_key = randKey();
        customer_3_key = randKey();
    }

    @Override
    public Script createInputScript() {
        // TODO: Create a script that can be spend using signatures from the bank and one of the customers
        ScriptBuilder builder = new ScriptBuilder();
        
        // check bank's key
        builder.data(bank_key.getPubKey());
        builder.op(OP_CHECKSIGVERIFY);
        // check customer 1-3's (any-one's) key
        builder.op(OP_1);
        builder.data(customer_1_key.getPubKey());
        builder.data(customer_2_key.getPubKey());
        builder.data(customer_3_key.getPubKey());
        builder.op(OP_3);
        builder.op(OP_CHECKMULTISIG);
        return builder.build();
    }

    @Override
    public Script createRedemptionScript(Transaction unsignedTransaction) {
        // Please be aware of the CHECK_MULTISIG bug!
        // TODO: Create a spending script
        ScriptBuilder builder = new ScriptBuilder();
        TransactionSignature b_txSig = sign(unsignedTransaction, bank_key);
        TransactionSignature c1_txSig = sign(unsignedTransaction, customer_1_key);
        TransactionSignature c2_txSig = sign(unsignedTransaction, customer_2_key);
        TransactionSignature c3_txSig = sign(unsignedTransaction, customer_3_key);

        builder.op(OP_2);   //to resolve the CHECK_MULTISIG bug
        builder.data(c1_txSig.encodeToBitcoin());
        builder.data(b_txSig.encodeToBitcoin());
        return builder.build();
    }
}